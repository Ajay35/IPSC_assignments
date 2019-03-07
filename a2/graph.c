#include <stdlib.h>
#include <stdio.h>
#define NUM_POINTS 6
#define NUM_COMMANDS 2

int main()
{
    char * commandsForGnuplot[] = {"set title \"No of Threads vs Execution time\"", "plot 'data.temp'"};
    int xvals[NUM_POINTS] = {1,2,3,4,6,8};
    double yvals[NUM_POINTS] = {4.663986 ,2.327392,1.596903,1.235001,0.829277,0.638845};
    FILE * temp = fopen("data.temp", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int i;
    for (i=0; i < NUM_POINTS; i++)
    {
    fprintf(temp, "%d %lf \n", xvals[i], yvals[i]); //Write the data to a temporary file
    }

    for (i=0; i < NUM_COMMANDS; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
    return 0;
}
