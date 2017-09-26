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

int main(void)
{
	// Variable Declarations
	FILE *data = NULL, *results = NULL;
	char line[MAX_LINE_SIZE], startMin[DIG_IN_TIME], endMin[DIG_IN_TIME];   
	FitbitData theData[MINUTES_PER_DAY],  // I'm not initializing these because the values will be overwritten eventually.
		totals = { {'\0'}, {0.0}, {0.0}, {0}, {0}, {0}, {0} };
	int i = 0, maxStepsMin = 0;
	double HR = 0.0;

	// Open file to read in data. Print off message to ensure successful opening.
	data = openFile("FitbitData.csv");

	// To ensure file is not proccessed without being open, use an 'if' statement
	if (data != NULL)
	{
		// Read first line (column headers)
		readLine(data, line);
		
		// Store the rest of the data into an array. Close the file once done.
		for (i = 0; i < MINUTES_PER_DAY; ++i)
		{
			readLine(data, line);
			storeData(&theData[i], line);
			clearLine(line);
		}
		fclose(data);
	}
	
	// Computations (check in Excel when done)
	compute_totals(theData, &totals);    //totals
	HR = avgHR(theData);		//avg HR
	maxStepsMin = maxSteps(theData);	//max steps over 24 hrs
	poorestSleep(startMin, endMin, theData);	//longest consecutive range of poor sleep
	
	// Print Results to Screen & File. Close file when done.
	results = fopen("Results.csv", "w");
	if (results != NULL)
	{
		outputHeaders(results);
		outputData(results, totals, HR, maxStepsMin, startMin, endMin);
		fclose(results);
	}

	return 0;
}