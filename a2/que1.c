
#include<unistd.h>
#include<stdlib.h>
#include<omp.h>
#include<stdio.h>
#define THREADS 10
#define N 100000000
int main ( ) {
// for static schedule 0.099098 seconds
// for dynamic schedule 3.88 seconds
// for guided schedule 0.100536 seconds 
// for dynamic scheduling with chunk size 100 : 0.116905 seconds 

int i;
struct timeval start, end;
gettimeofday(&start, NULL);
printf("Running %d iterations on %d threads dynamically.\n", N, THREADS);
//#pragma omp parallel for schedule(dynamic) num_threads(THREADS)
#pragma omp parallel for schedule(dynamic,100) num_threads(THREADS)
//#pragma omp parallel for schedule(static) num_threads(THREADS)
//#pragma omp parallel for schedule(guided) num_threads(THREADS)
for (i = 0; i < N; i++) {
/* a loop that doesn’t take very long */
}
/* all threads done */
printf("All done!\n");
gettimeofday(&end, NULL);
float delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
         end.tv_usec - start.tv_usec) / 1.e6;
printf("%f seconds \n"	,delta );
return 0;
}
