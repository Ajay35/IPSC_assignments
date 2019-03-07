#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<unistd.h>

#define THREADS 4
#define N 16
int main(){

// guided schedule with 4 threads 36.006573 seconds 
// dynamic schedule with 4 threads 36.004601 seconds 
// static schedule with 4 threads 54.004936 seconds 
 
int i;
struct timeval start, end;
gettimeofday(&start, NULL);
//#pragma omp parallel for schedule(guided) num_threads(THREADS)
#pragma omp parallel for schedule(dynamic) num_threads(THREADS)
//#pragma omp parallel for schedule(static) num_threads(THREADS)
//#pragma omp parallel for schedule(static) num_threads(THREADS)
for (i = 0; i < N; i++) {
/* wait for i seconds */
sleep(i);
printf("Thread %d has completed iteration %d.\n", omp_get_thread_num( ), i);
}
/* all threads done */
printf("All done!\n");
gettimeofday(&end, NULL);
float delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
         end.tv_usec - start.tv_usec) / 1.e6;
printf("%f seconds \n"	,delta );
return 0;
}
