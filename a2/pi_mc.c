#include <stdio.h>
#include <omp.h>
#include "random.h"
static long num_trials = 100000000;
int main ()
{
long i; long Ncirc = 0;
double pi, x, y, test, time;
double r = 1.0;
// radius of circle. Side of squrare is 2*r
time = omp_get_wtime();
#pragma omp parallel
{
#pragma omp ...
printf(" %d threads ",omp_get_num_threads());
seed(-r, r);
#pragma omp for reduction(+:Ncirc) private(i,x,y,test)
for(i=0;i<num_trials; i++)
{
x = drandom();
y = drandom();
test = x*x + y*y;
if (test <= r*r) Ncirc++;
}
}
pi = 4.0 * ((double)Ncirc/(double)num_trials);
printf("\n %ld trials, pi is %lf ",num_trials, pi);
printf(" in %lf seconds\n",omp_get_wtime()-time);
return 0;
}

/*

 1 threads 
 100000000 trials, pi is 3.141494  in 4.777138 seconds

real	0m4.780s
user	0m4.776s
sys	0m0.004s


 2 threads  2 threads 
 100000000 trials, pi is 3.141854  in 2.681743 seconds

real	0m2.685s
user	0m5.364s
sys	0m0.001s


 3 threads  3 threads  3 threads 
 100000000 trials, pi is 3.141817  in 2.171740 seconds

real	0m2.174s
user	0m6.104s
sys	0m0.004s

 4 threads  4 threads  4 threads  4 threads 
 100000000 trials, pi is 3.141760  in 1.717287 seconds

real	0m1.720s
user	0m6.773s
sys	0m0.000s

 6 threads  6 threads  6 threads  6 threads  6 threads  6 threads 
 100000000 trials, pi is 3.141749  in 1.779200 seconds

real	0m1.782s
user	0m6.778s
sys	0m0.004s



|************************** ON ABACUS**********************|

[ipsc17@abacus ~]$ export OMP_NUM_THREADS=1
[ipsc17@abacus ~]$ time ./pi_mc 
 1 threads 
 100000000 trials, pi is 3.141494  in 4.663986 seconds

real	0m4.665s
user	0m4.660s
sys	0m0.001s
[ipsc17@abacus ~]$ export OMP_NUM_THREADS=2
[ipsc17@abacus ~]$ time ./pi_mc 
 2 threads  2 threads 
 100000000 trials, pi is 3.141854  in 2.327392 seconds

real	0m2.329s
user	0m4.638s
sys	0m0.000s
[ipsc17@abacus ~]$ export OMP_NUM_THREADS=3
[ipsc17@abacus ~]$ time ./pi_mc 
 3 threads  3 threads  3 threads 
 100000000 trials, pi is 3.141817  in 1.596903 seconds

real	0m1.599s
user	0m4.774s
sys	0m0.003s
[ipsc17@abacus ~]$ export OMP_NUM_THREADS=4
[ipsc17@abacus ~]$ time ./pi_mc 
 4 threads  4 threads  4 threads  4 threads 
 100000000 trials, pi is 3.141760  in 1.235001 seconds

real	0m1.237s
user	0m4.850s
sys	0m0.002s
[ipsc17@abacus ~]$ export OMP_NUM_THREADS=6
[ipsc17@abacus ~]$ time ./pi_mc 
 6 threads  6 threads  6 threads  6 threads  6 threads  6 threads 
 100000000 trials, pi is 3.141749  in 0.829277 seconds

real	0m0.831s
user	0m4.935s
sys	0m0.001s



(a) What is the speedup on 6 cores relative to 1 core?
(b) What is the speedup of 4 cores relative to 1 core?
(c) Why do you think the time taken on 4 cores is not 1/4th of the time taken on 1 core?









*/
