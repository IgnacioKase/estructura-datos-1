#include <stdlib.h>
#include <stdio.h>
#define NUM_POINTS 5
#define NUM_COMMANDS 2

int main()
{
    char * commandsForGnuplot[] = {"set terminal dumb set title \"Evolución de los casos confirmados\"",
	                           "plot 'diarios.temp' with lines, 'acumulados.temp' with lines"};
    double xvals[NUM_POINTS] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double yvals[NUM_POINTS] = {5.0 ,3.0, 1.0, 3.0, 5.0};
    FILE * temp = fopen("diarios.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int i;
    for (i=0; i < NUM_POINTS; i++)
    {
        fprintf(temp, "%lf\t %lf\t \n", xvals[i], yvals[i]); //Write the data to a temporary file
    }

    double xvals2[NUM_POINTS] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double yvals2[NUM_POINTS] = {1.0, 2.0, 3.0, 4.0, 5.0};
    FILE * temp2 = fopen("acumulados.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    int j;
    for (j=0; j < NUM_POINTS; j++)
    {
        fprintf(temp2, "%lf\t %lf\t \n", xvals2[j], yvals2[j]); //Write the data to a temporary file
    }


    for (i=0; i < NUM_COMMANDS; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
    return 0;
}
