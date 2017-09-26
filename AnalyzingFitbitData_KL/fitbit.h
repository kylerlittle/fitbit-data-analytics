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


#ifndef ASSIGNMENT1_FITBIT
#define ASSIGNMENT1_FITBIT

/* Standard Libraries Included */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Defined Macroconstants */
#define MAX_LINE_SIZE 65
#define MINUTES_PER_DAY 1440
#define DIG_IN_TIME 9

/* Defined Types */
typedef enum sleep
{
	NONE, ASLEEP, AWAKE, REALLY_AWAKE
} Sleep;
typedef struct fitbit
{
	char minute[DIG_IN_TIME];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

/* Function Prototypes */

// Reading in Data

/*************************************************************
* Function: openFile                                        *
* Description: This function opens a file for read mode and *
				prints a message whether successful or not. *
* Input parameters: File                                    *
* Returns: File Type                                        *
* Preconditions: None                                       *
* Postconditions: File is open (hopefully).                 *
*************************************************************/
FILE * openFile(FILE *f);

/*************************************************************
* Function: readLine	                                    *
* Description: This function reads in a single line of data *
			   from the file "data" and stores a maximum of *
			   64 characters into the string "line"			*
* Input parameters: string, file                            *
* Returns: nothing                                          *
* Preconditions: File is open for "read" mode. Line is a
				 string of at least size 65. *
* Postconditions: none                                      *
*************************************************************/
void readLine(FILE *data, char line[]);

/*************************************************************
* Function: storeData                                       *
* Description: stores the data from "line" into the seven 
			   fields of the FitbitData struct *
* Input parameters: string, pointer to a struct
* Returns: nothing                                          *
* Preconditions: line has 7 "records" of data separated by commas
*
* Postconditions: FitbitData struct indirectly modified            
*************************************************************/
void storeData(FitbitData *pData, char line[]);

/*************************************************************
* Function: clearLine                                       *
* Description: This function clears the contents of "line"  *
			   and sets each entry to the null character    *
* Input parameters: line                                    *
* Returns: nothing                                          *
* Preconditions: line is contiguous memory                  *
* Postconditions: none                                      *
*************************************************************/
void clearLine(char line[]);


// Performing Computations

/*************************************************************
* Function: compute_totals  
* Description: This function sums the calories, distance,
			   floors, and steps entries from the all_data
			   array. It stores them in pTotals indirectly.
* Input parameters: array of FitbitData struct, pointer to struct    
* Returns: nothing        
* Preconditions: none
* Postconditions: none
*************************************************************/
void compute_totals(FitbitData all_data[], FitbitData *pTotals);

/*************************************************************
* Function: avgHR
* Description: Computes the average heartRate of nonempty entries
			   in the array of FitbitData struct
* Input parameters: FitbitData struct array
* Returns: the average heartrate
* Preconditions: all_data represents contiguous memory
* Postconditions: none
*************************************************************/
double avgHR(FitbitData all_data[]);

/*************************************************************
* Function: maxSteps
* Description: Determines the maximum number of steps taken
			   during a one minute period.
* Input parameters: all_data struct
* Returns: max steps in single minute
* Preconditions: all_data represents contiguous memory
* Postconditions: none
*************************************************************/
unsigned int maxSteps(FitbitData all_data[]);

/*************************************************************
* Function: poorestSleep
* Description: Determines the "worst period of sleep"-- defined by
			   the highest sum of consecutive sleepLevels > 1.
			   Stores the starting and ending minutes of the 
			   worst period of sleep into start and end.
* Input parameters: all_data struct, start & end char arrays
* Returns: nothing
* Preconditions: all_data represents contiguous memory, start
				 and end are char arrays size 9
* Postconditions: none
*************************************************************/
void poorestSleep(char start[], char end[], FitbitData all_data[]);


// Outputting Results

/*************************************************************
* Function: outputHeaders
* Description: Prints the "headers" for the important data to
			   the screen and output csv file.
* Input parameters: output data file
* Returns: nothing
* Preconditions: output file is opened for mode write
* Postconditions: data printed to file and screen
*************************************************************/
void outputHeaders(FILE * output);

/*************************************************************
* Function: outputData
* Description: Prints the important data (total steps taken,
			   total distance walked, avg HR, etc.) to the screen 
			   and output csv file.
* Input parameters: output data file
* Returns: nothing
* Preconditions: output file is opened for mode write
* Postconditions: data printed to file and screen
*************************************************************/
void outputData(FILE * output, FitbitData totals, double avgHR, unsigned int maxSteps,
	char *start, char *end);

#endif