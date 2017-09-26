/*******************************************************************************
* Programmer: Kyler Little													  *
* Class: CptS 121; Lab Section 6                                              *
* Programming Assignment: Analyzing Fitbit Data (PA #1)                       *
* Date: 1/18/2017                                                             *
*                                                                             *
* Description: This program calculates statistics on Fitbit Data		      *
*              read in from a csv file. It then outputs the data to           *
*			   both the screen and a "results" csv file.					  *
*                                                                             *
* Relevant Formulas: Refer to each function definition.                       *
*                                                                             *
* Format of record in input file (input.dat): 00:05:07	(minute string)       *
*                                             0.23892	(calories double)     *
*											  0.023438	(distance double)     *
*			    							  3		(floors unsigned int)	  *
*			    							  67	(heartRate unsigned int)  *
*			    							  33	(steps unsigned int)	  *
*			    							  1		(sleepLevel Sleep)		  *
*                                                                             *
* Format of output file (output.dat): See problem specification.              *
******************************************************************************/


#include "fitbit.h"

void outputHeaders(FILE * output)
{
	fprintf(output, "Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
	printf("Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
}
void outputData(FILE * output, FitbitData totals, double avgHR, unsigned int maxSteps,
	char *start, char *end)
{
	fprintf(output, "%.8lf,%.8lf,%u,%u,", totals.calories, totals.distance, totals.floors, totals.steps);
	fprintf(output, "%.2lf,%u,%s,%s\n", avgHR, maxSteps, start, end);
	printf("%.8lf,%.8lf,%u,%u,", totals.calories, totals.distance, totals.floors, totals.steps);
	printf("%.2lf,%u,%s,%s\n", avgHR, maxSteps, start, end);
}