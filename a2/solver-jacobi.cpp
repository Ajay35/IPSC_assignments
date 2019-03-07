#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
using namespace std;
extern double eps;
extern double **New_Matrix(int m, int n);
extern void Delete_Matrix(double **matrix);
int solver(double **a, int n)
{
	printf("in solver");
	int i,j;
	double h;
	double diff;
	int k = 0;
	double **b = New_Matrix(n,n);
	if (b == NULL) {
	cerr << "Jacobi: Can’t allocate matrix\n";
	exit(1);
	}
	 
	
	do {
	    #pragma omp parallel private(j,h)
	    {
	     diff = 0;
	    #pragma omp for schedule(static)
	     for (i=1; i<n-1; i++) {
	      for (j=1; j<n-1; j++) { 
	       b[i][j] = 0.25 * (a[i][j-1] + a[i-1][j]+a[i+1][j] + a[i][j+1]);
	       h = fabs(a[i][j] - b[i][j]);
	       if (h > diff){
		    #pragma omp atomic write       	 
	       	    diff = h;
	       } 
	      }
	    }
	/*
	** Copy intermediate result into matrix ’a’
	*/
	   #pragma omp for schedule(static)
	    for (i=1; i<n-1; i++) {
	      for (j=1; j<n-1; j++) {
		 a[i][j] = b[i][j];
	      }
	    }
	k++;
	}
	} while (diff > eps);
	
	Delete_Matrix(b);
	return k;
}



/*



[ipsc17@abacus ~]$ ./a.out 1000
Result: 353 iterations
  a[ 874][ 125] = 3.54305644933678421e-21
  a[ 874][  62] = 2.57130479031213425e-06
  a[ 500][ 500] = 0
  a[  62][ 874] = 2.57130479031213467e-06
  a[ 125][ 874] = 3.54305644933678421e-21
Runtime: 7.073 s
Performance: 0.199 GFlop/s
[ipsc17@abacus ~]$ export OMP_NUM_THREADS=2
[ipsc17@abacus ~]$ ./a.out 1000
Result: 706 iterations
  a[ 874][ 125] = 3.54305644933678421e-21
  a[ 874][  62] = 2.57130479031213425e-06
  a[ 500][ 500] = 0
  a[  62][ 874] = 2.57130479031213467e-06
  a[ 125][ 874] = 3.54305644933678421e-21
Runtime: 3.543 s
Performance: 0.794 GFlop/s
[ipsc17@abacus ~]$ export OMP_NUM_THREADS=4
[ipsc17@abacus ~]$ ./a.out 1000
Result: 899 iterations
  a[ 874][ 125] = 3.54305644933678421e-21
  a[ 874][  62] = 2.57130479031213425e-06
  a[ 500][ 500] = 0
  a[  62][ 874] = 2.57130479031213467e-06
  a[ 125][ 874] = 3.54305644933678421e-21
Runtime: 1.838 s
Performance: 1.948 GFlop/s
[ipsc17@abacus ~]$ export OMP_NUM_THREADS=6
[ipsc17@abacus ~]$ ./a.out 1000
Result: 1020 iterations
  a[ 874][ 125] = 3.54305644933678421e-21
  a[ 874][  62] = 2.57130479031213425e-06
  a[ 500][ 500] = 0
  a[  62][ 874] = 2.57130479031213467e-06
  a[ 125][ 874] = 3.54305644933678421e-21
Runtime: 1.241 s
Performance: 3.275 GFlop/s
[ipsc17@abacus ~]$ export OMP_NUM_THREADS=10
[ipsc17@abacus ~]$ ./a.out 1000
Result: 999 iterations
  a[ 874][ 125] = 3.54305644933678421e-21
  a[ 874][  62] = 2.57130479031213425e-06
  a[ 500][ 500] = 0
  a[  62][ 874] = 2.57130479031213467e-06
  a[ 125][ 874] = 3.54305644933678421e-21
Runtime: 0.821 s
Performance: 4.850 GFlop/s
[ipsc17@abacus ~]$ export OMP_NUM_THREADS=20
[ipsc17@abacus ~]$ ./a.out 1000
Result: 1352 iterations
  a[ 874][ 125] = 3.54305644933678421e-21
  a[ 874][  62] = 2.57130479031213425e-06
  a[ 500][ 500] = 0
  a[  62][ 874] = 2.57130479031213467e-06
  a[ 125][ 874] = 3.54305644933678421e-21
Runtime: 0.853 s
Performance: 6.312 GFlop/s
[ipsc17@abacus ~]$ 
*/
