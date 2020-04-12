#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "util.h"


void util::errorMessage(int i, int j, int k)
{
	//displays an error if the text file couldn't be opened
	if (i == 0)
	{
		printf("There was a problem opening file Ginput.txt for reading.\n");
	}
	//displays an error if there is no graph
	if (i == 1)
	{
		printf("Error: There is no graph to print.\n");
	}
	//displays an error if there is no graph when prompted to do dijkstra's algorithm
	if (i == 2)
	{
		printf("Error: There is no graph to run Dijkstra's algorithm on.\n");
	}
	//displays an error if the numbers specified in the text file are wrong
	if (i == 3)
	{
		printf("Error: The number of edges is less than specified in the beginning of the file.\n");
	}
	//displays an error if the user wants to reach an unreachable node
	if (i == 4)
	{
		printf("Sorry, node %d is not reachable from node %d.\n", j, k);
	}
	//displays an error if the user enters a wrong flag value
	if (i == 5)
	{
		printf("Error: Invalid flag value.\n");
	}
	//displays an error if the nodes entered for DSP are wrong
	if (i == 6)
	{
		printf("Error: One or more of the nodes is invalid.\n");
	}
	//displays an error if the file contains a negative weight
	if (i == 7)
	{
		printf("Error: You cannot have a negative weight.\n");
	}
	//displays an error if the file has negative vertices
	if (i == 8)
	{
		printf("Error: A vertex must be a positive, non-zero value.\n");
	}

}
