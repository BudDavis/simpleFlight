#if 0
#include <unistd.h>

#include <iostream>
#include <string>

#include <FGFDMExec.h>

#include "json.hpp"
#include "interface.h"


JSBSim::FGFDMExec fdmex;

std::string copy_from_JSBSim ()
{
}

void copy_to_JSBSim (std::string S)
{
}

//termsVec in  = {terms_t("aaa","bbbb", []{return fdmex.GetPropagate()->GetLocation().GetLongitudeDeg(); } ) };
//termsVec in  = {terms_t("aaa","bbbb", []{return fdmex.GetPropagate()->GetLocation().GetLongitudeDeg() } ) };
//termsVec out = {terms_t("aaa","bbb")};
//fdmex.GetPropagate()->GetLocation().GetLongitudeDeg()
#if 0
    SG_LOG( SG_FLIGHT, SG_INFO, "  Bank Angle: "
            << Propagate->GetEuler(FGJSBBase::ePhi)*RADTODEG << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  Pitch Angle: "
            << Propagate->GetEuler(FGJSBBase::eTht)*RADTODEG << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  True Heading: "
            << Propagate->GetEuler(FGJSBBase::ePsi)*RADTODEG << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  Latitude: "
            << Propagate->GetLocation().GetLatitudeDeg() << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  Longitude: "
            << Propagate->GetLocation().GetLongitudeDeg() << " deg" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  Altitude: "
            << Propagate->GetAltitudeASL() << " feet" );
    SG_LOG( SG_FLIGHT, SG_INFO, "  loaded initial conditions" );

 <latitude unit="DEG">   47.0 </latitude>
  <longitude unit="DEG"> 122.0 </longitude>
  <phi>         0.0 </phi>
  <theta>       0.0 </theta>
  <psi unit="DEG">       150.0 </psi>
  <altitude>    2000.00 </altitude>


   FCS->SetDaCmd( globals->get_controls()->get_aileron());
    FCS->SetRollTrimCmd( globals->get_controls()->get_aileron_trim() );
    FCS->SetDeCmd( globals->get_controls()->get_elevator());
    FCS->SetPitchTrimCmd( globals->get_controls()->get_elevator_trim() );
    FCS->SetDrCmd( -globals->get_controls()->get_rudder() );
    FCS->SetDsCmd( globals->get_controls()->get_rudder() );
    FCS->SetYawTrimCmd( -globals->get_controls()->get_rudder_trim() );
    FCS->SetDfCmd( globals->get_controls()->get_flaps() );
    FCS->SetDsbCmd( globals->get_controls()->get_speedbrake() );
    FCS->SetDspCmd( globals->get_controls()->get_spoilers() );
#endif

//JSBSim::FGFDMExec fdmex;
//jsbsimInterface_t iface(fdmex);

//termsVec in  = {terms_t("aaa","bbbb", []{return fdmex.GetPropagate()->GetLocation().GetLongitudeDeg(); } ) };
// input files
std::string ac = "c172r";
std::string scr = "";
std::string reset = "reset00";

int exitFlag = 0;

int main(int argc, char* argv[])
{
      std::cout << "count of args " << argc << std::endl;
      for (int i=0;i<argc;i++)
      {
         std::cout << "  " << argv[i] << std::endl;
      }
/* the arguments must be:
 *                  websocket port
 *                  aircraft xml file
 *                  script xml file
 *                  reset xml file
 */
//jsbsimInterface_t iface(fdmex);
        if (fdmex.LoadModel( ac , true ) )
        {
           fdmex.RunIC(); // loop JSBSim once w/o integrating
           std::cout << "the ic object is " << fdmex.GetIC() << std::endl;
           while (fdmex.Run() && !exitFlag) 
           {
               usleep ( 33333 );
           }
        }
        //copy_to_JSBsim(); // copy control inputs to JSBSim
        //fdmex->RunIC(); // loop JSBSim once w/o integrating
        //copy_from_JSBsim(); // update the bus
#if 0
        fdmex->LoadScript( ScriptName ); // the script loads the aircraft and
        result = FDMExec->Run();
        while (result) 
        { // cyclic execution
           result = FDMExec->Run(); // execute JSBSim
        }
#endif
	printf("normal exit\n");
	return 0;
}
#endif

//////////////////////////////////////////////////////////
#include "sim.hpp"
#include "simConnection.hpp"
// this is the simulator object.  only 1 of them
// (note to self.  JSBSim is not thread safe, only 1 instance at a time)

static sim *Sim = nullptr;

//////////////////////////////////////////////////////////

#include <websocketpp/config/asio_no_tls.hpp>

#include <websocketpp/server.hpp>

#include <fstream>
#include <iostream>
#include <set>
#include <streambuf>
#include <string>

/**
 * The telemetry server accepts connections and sends a message every second to
 * each client containing an integer count. This example can be used as the
 * basis for programs that expose a stream of telemetry data for logging,
 * dashboards, etc.
 *
 * This example uses the timer based concurrency method and is self contained
 * and singled threaded. Refer to telemetry client for an example of a similar
 * telemetry setup using threads rather than timers.
 *
 * This example also includes an example simple HTTP server that serves a web
 * dashboard displaying the count. This simple design is suitable for use 
 * delivering a small number of files to a small number of clients. It is ideal
 * for cases like embedded dashboards that don't want the complexity of an extra
 * HTTP server to serve static files.
 *
 * This design *will* fall over under high traffic or DoS conditions. In such
 * cases you are much better off proxying to a real HTTP server for the http
 * requests.
 */
class telemetry_server {
public:
    typedef websocketpp::connection_hdl connection_hdl;
    typedef websocketpp::server<websocketpp::config::asio> server;

    telemetry_server() : m_count(0) {
        // set up access channels to only log interesting things
        m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
        m_endpoint.set_access_channels(websocketpp::log::alevel::access_core);
        m_endpoint.set_access_channels(websocketpp::log::alevel::app);

        // Initialize the Asio transport policy
        m_endpoint.init_asio();

        // Bind the handlers we are using
        using websocketpp::lib::placeholders::_1;
        using websocketpp::lib::bind;
        m_endpoint.set_open_handler(bind(&telemetry_server::on_open,this,_1));
        m_endpoint.set_close_handler(bind(&telemetry_server::on_close,this,_1));
        m_endpoint.set_http_handler(bind(&telemetry_server::on_http,this,_1));
        using websocketpp::lib::placeholders::_2;
        m_endpoint.set_message_handler(bind(&telemetry_server::on_message,this,_1,_2));
    }

    void run(std::string docroot, uint16_t port) {
        std::stringstream ss;
        ss << "Running telemetry server on port "<< port <<" using docroot=" << docroot;
        m_endpoint.get_alog().write(websocketpp::log::alevel::app,ss.str());
        
        m_docroot = docroot;
        
        // listen on specified port
        m_endpoint.listen(port);

        // Start the server accept loop
        m_endpoint.start_accept();

        // Set the initial timer to start telemetry
        set_timer();

        // Start the ASIO io_service run loop
        try {
            m_endpoint.run();
        } catch (websocketpp::exception const & e) {
            std::cout << e.what() << std::endl;
        }
    }

    void set_timer() {
        m_timer = m_endpoint.set_timer(
            33,
            websocketpp::lib::bind(
                &telemetry_server::on_timer,
                this,
                websocketpp::lib::placeholders::_1
            )
        );
    }

    void on_timer(websocketpp::lib::error_code const & ec) {
        if (ec) {
            // there was an error, stop telemetry
            m_endpoint.get_alog().write(websocketpp::log::alevel::app,
                    "Timer Error: "+ec.message());
            return;
        }
        
        std::stringstream val;
        val << "count is " << m_count++;
        
        // Broadcast count to all connections
        con_list::iterator it;
        for (it = m_connections.begin(); it != m_connections.end(); ++it) {
            m_endpoint.send(*it,val.str(),websocketpp::frame::opcode::text);
        }
        
        if (Sim) {
           Sim->tick();
        } 
        // set timer for next telemetry check
        set_timer();
    }

    void on_http(connection_hdl hdl) {
        // Upgrade our connection handle to a full connection_ptr
        server::connection_ptr con = m_endpoint.get_con_from_hdl(hdl);
    
        std::ifstream file;
        std::string filename = con->get_resource();
        std::string response;
    
        m_endpoint.get_alog().write(websocketpp::log::alevel::app,
            "http request1: "+filename);
    
        if (filename == "/") {
            filename = m_docroot+"index.html";
        } else {
            filename = m_docroot+filename.substr(1);
        }
        
        m_endpoint.get_alog().write(websocketpp::log::alevel::app,
            "http request2: "+filename);
    
        file.open(filename.c_str(), std::ios::in);
        if (!file) {
            // 404 error
            std::stringstream ss;
        
            ss << "<!doctype html><html><head>"
               << "<title>Error 404 (Resource not found)</title><body>"
               << "<h1>Error 404</h1>"
               << "<p>The requested URL " << filename << " was not found on this server.</p>"
               << "</body></head></html>";
        
            con->set_body(ss.str());
            con->set_status(websocketpp::http::status_code::not_found);
            return;
        }
    
        file.seekg(0, std::ios::end);
        response.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
    
        response.assign((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
        con->set_body(response);
        con->set_status(websocketpp::http::status_code::ok);
    }

    void on_open(connection_hdl hdl) {
        if (!Sim) {
           std::cout << "new connection" << std::endl;
           Sim = new sim();
           // lets pass in some arguments to select the files, etc...
        }
        m_connections.insert(hdl);
    }

    void on_close(connection_hdl hdl) {
//////////////////////////////////////////////////////////
//  on close connection code here
//////////////////////////////////////////////////////////
        m_connections.erase(hdl);
    }

typedef server::message_ptr message_ptr;

// Define a callback to handle incoming messages
void on_message(websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get() 
              << " and message (" << msg->get_payload().size() << "): " << msg->get_payload()
              << std::endl;
   #if 0 
    try {
        s->send(hdl, msg->get_payload(), msg->get_opcode());
    } catch (websocketpp::exception const & e) {
        std::cout << "Echo failed because: "
                  << "(" << e.what() << ")" << std::endl;
    }
    #endif
}

private:
    typedef std::set<connection_hdl,std::owner_less<connection_hdl>> con_list;
    
    server m_endpoint;
    con_list m_connections;
    server::timer_ptr m_timer;
    
    std::string m_docroot;
    
    // Telemetry data
    uint64_t m_count;
};

int main(int argc, char* argv[]) {
    telemetry_server s;

    std::string docroot;
    uint16_t port = 9002;

    if (argc == 1) {
        std::cout << "Usage: telemetry_server [documentroot] [port]" << std::endl;
        return 1;
    }
    
    if (argc >= 2) {
        docroot = std::string(argv[1]);
    }
        
    if (argc >= 3) {
        int i = atoi(argv[2]);
        if (i <= 0 || i > 65535) {
            std::cout << "invalid port" << std::endl;
            return 1;
        }
        
        port = uint16_t(i);
    }


    s.run(docroot, port);
    return 0;
}
