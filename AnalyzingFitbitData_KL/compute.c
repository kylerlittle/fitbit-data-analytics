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

void compute_totals(FitbitData all_data[], FitbitData *pTotals)
{
	int i = 0;
	for (i = 0; i < MINUTES_PER_DAY; ++i)
	{
		pTotals->calories += all_data[i].calories;
		pTotals->distance += all_data[i].distance;
		pTotals->floors += all_data[i].floors;
		pTotals->steps += all_data[i].steps;
	}
}
double avgHR(FitbitData all_data[])
{
	int i = 0, sum = 0, data_points = 0;
	double avg;
	for (i = 0; i < MINUTES_PER_DAY; ++i)
	{
		if (all_data[i].heartRate != 0)
		{
			sum += all_data[i].heartRate;
			++data_points;
		}
	}
	return avg = sum / (double) data_points; //one needs to be cast as a double
}
unsigned int maxSteps(FitbitData all_data[])
{
	int i = 0, max = 0;
	max = all_data[0].steps;
	for (i = 0; i < MINUTES_PER_DAY; ++i)
	{
		if (all_data[i].steps >= max)
		{
			max = all_data[i].steps;
		}
	}
	return (unsigned int) max;
}
void poorestSleep(char start[], char end[], FitbitData all_data[])
{
	int i = 0, sum = 0, worst_sum = 0, streak = 0, left = 0, right = 0;
	for (i = 0; i < MINUTES_PER_DAY; ++i)
	{
		if (all_data[i].sleepLevel >= AWAKE)
		{
			sum += all_data[i].sleepLevel;
			++streak;
		}
		if (sum > worst_sum)
		{    // we want to keep the greatest sum
			worst_sum = sum;
			left = i - (streak - 1);  //subtract one from streak so left is correct index
			right = i;  //we want to keep i if it's the worst sum
		}
		if (all_data[i + 1].sleepLevel >= AWAKE && all_data[i].sleepLevel < AWAKE)
		{  //if restarting the sum sequence (next data point is valid & current is invalid), reset sum
			sum = 0;
			streak = 0;
		}
	}
	strcpy(start, all_data[left].minute);   //retain the results
	strcpy(end, all_data[right].minute);
}