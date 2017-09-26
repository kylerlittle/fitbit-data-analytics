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

FILE * openFile(FILE *f)
{
	FILE *file = NULL;
	file = fopen(f, "r");
	if (file != NULL)
	{
		printf("File opened successfully!\n");
	}
	else
	{
		printf("File didn't open! Try again!\n");
	}
	return file;
}
void readLine(FILE *data, char line[])
{
	char read_in[MAX_LINE_SIZE];
	fgets(read_in, MAX_LINE_SIZE - 1, data);
	strncpy(line, read_in, MAX_LINE_SIZE - 1);
}
void storeData(FitbitData *pData, char line[])
{
	char *pTemp = NULL;
	pTemp = strtok(line, ",");
	strncpy(pData->minute, pTemp, DIG_IN_TIME);   //store first item
	pTemp = strtok(NULL, ",");
	pData->calories = (double)atof(pTemp);  //store calories burned (double)
	pTemp = strtok(NULL, ",");
	pData->distance = (double)atof(pTemp);  //store distance walked (double)
	pTemp = strtok(NULL, ",");
	pData->floors = (unsigned int)atoi(pTemp);  //stores floors climbed (unsigned int)
	pTemp = strtok(NULL, ",");
	pData->heartRate = (unsigned int)atoi(pTemp);
	if (*pTemp != '0' && *pTemp != NULL)   //indicating a nonempty record
	{  //for heart rate, the reading call be null because the person took off the HR monitor!
		pTemp = strtok(NULL, ",");   //if it's not empty, we need to still look for a delimiter
	}
	pData->steps = (unsigned int)atoi(pTemp);
	pTemp = strtok(NULL, ",");
	pData->sleepLevel = (Sleep)atoi(pTemp);
}
void clearLine(char line[])
{
	int i = 0;
	for (i = 0; line[i] != '\n'; ++i)
	{
		line[i] = '\0';
	}
}