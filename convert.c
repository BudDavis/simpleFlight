#include <stdio.h>
// for some reason this define is required for clock_gettime()
//
// see also, "get off my lawn..."
#define __USE_POSIX199309
#include <time.h>

double diffTime(struct timespec t0, struct timespec t1)
{
   // This function calculates the difference between two
   // timespec's in seconds.
   return ((t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9);
}

int main()
{
   struct timespec t0; // pronounced "T ZERO"
   struct timespec t1; //            "T 1"

   // using clock_gettime() on small segments of code will
   // give highly variable answers.  suggest doing it many times
   // in a loop and taking the average.
   clock_gettime(CLOCK_REALTIME, &t0);
   printf("hello\n");
   clock_gettime(CLOCK_REALTIME, &t1);

   printf("printing hello took %f seconds\n", diffTime(t0, t1));

   return 0;
}
