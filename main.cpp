#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "graph.h"
#include "heap.h"
#include "util.h"

using namespace std;

int main()
{
	//creates inFile and dummyLine to read input
	ifstream inFile;
	string dummyLine;

	//creates V, E, and x for creating the graph
	int V; int E; int x;

	//creates s, t and flag for dijkstra's algoritm
	int s; int t; int flag;

	//creates the classes used
	graph g;
	//heap h;
	util utilFunc;

	//opens a file called "Ginput.txt"
	inFile.open("Ginput.txt");
	//closes the program if there is no file
	if (!inFile) {
		printf("Error: There is no file.");
		exit(0);
	}
	//determines the V and E values from the file
	else
	{
		inFile >> x;
		V = x;
		inFile >> x;
		E = x;
	}
	//closes the file
	inFile.close();

	//checks to see V and E have valid values
	if (V <= 0 || E <= 0)
	{
		printf("Error: You cannot have a negative amount of edges or vertices.\n");
		exit(0);
	}

	//creates the graph
	struct Graph* newGraph = g.createGraph(V, E);

	//input char
	char c;

	while (1)
	{
		c = getchar();

		switch (c)
		{
		//case i reads and creates the graph
		case 'i':
		case 'I':
		{
			printf("COMMAND: %c\n", c);

			//dynamically creates a 1d array			
			int *array1 = new int[E * 3];
			int index = 0;

			//helper variables for determining lines in file
			int numbersRead = 0;
			int linesRead = 0;

			//prints an error message if the file 
			inFile.open("Ginput.txt");
			if (!inFile) {
				utilFunc.errorMessage(0, 0, 0);
				break;
			}
			else
			{
				//clears the first line containing the information on edges & vertices
				getline(inFile, dummyLine);

				//reads the numbers from the file. checks to see if linesRead is less than the amount specified
				while (inFile >> x && linesRead < E)
				{
					//adds the numbers into an array
					numbersRead++;
					array1[index] = x;
					index++;
					//increments the lines read when three numbers are read
					if (numbersRead == 3)
					{
						linesRead++;
						numbersRead = 0;
					}
				}

				//checks for any negative numbers in the file
				for (int i = 0; i < E * 3; i++)
				{
					if (array1[i] < 0)
					{
						printf("Error: You cannot have a negative weights or negative vertices.\n");
						exit(0);
					}
				}

				//outputs an error message if there aren't enough numbers in the file
				if (linesRead < E)
				{
					utilFunc.errorMessage(3, 0, 0);
					exit(0);
				}
				//closes the file
				inFile.close();

				//dynamically creates the two dimensional array for creating the graph
				int** array2 = new int*[E];
				for (int i = 0; i < E; i++)
					array2[i] = new int[3];

				//helper variable for changing from a 1d array into a 2d array
				int at = 0;

				//adds the values from the 1d array into the 2d array
				for (int i = 0; i < E; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						array2[i][j] = array1[at];
						at++;
					}
				}
				//deletes the 1d array
				delete[] array1;

				//if a graph already exists, it breaks
				if (newGraph->array[0].head != NULL)
				{
					break;
				}
				//if no graph exists, a new one is created
				else
				{
					//adds edges into the graph
					for (int i = 0; i < E; i++)
					{
						g.addEdge(newGraph, array2[i][0] - 1, array2[i][1] - 1, array2[i][2]);
					}

				}

				//delete[] array2;
				break;
			}
		}

		//case 'e' terminates the program
		case 'e':
		case 'E':
			printf("COMMAND: %c\n", c);
			printf("The program is going to be terminated.\n");
			exit(0);

		//case 'w' prints the graph
		case 'w':
		case 'W':
			printf("COMMAND: %c\n", c);
			//displays an error message if no graph is present
			if (newGraph->array[0].head == NULL)
				utilFunc.errorMessage(1, 0, 0);
			//prints the graph if it exists
			else
				g.printGraph(newGraph);
			break;

		//case 'c' implements dijkstra's algorithm
		case 'c':
		case 'C':
			//takes three variables
			cin >> s; //starting vertex
			cin >> t; //ending vertex
			cin >> flag; //flag (1 for path, 0 for length)
			printf("COMMAND: %c %d %d %d.\n", c, s, t, flag);

			//displays an error if there is no graph
			if (newGraph->array[0].head == NULL)
			{
				utilFunc.errorMessage(2, 0, 0);
				break;
			}
			//displays an error if the start and end values are out of range
			else if (s > newGraph->V || t > newGraph->V || s <= 0 || t <= 0)
			{
				utilFunc.errorMessage(6, 0, 0);
				//displays an error if the flag value is an invalid value
				if (flag < 0 || flag > 1)
					utilFunc.errorMessage(5, 0, 0);
				break;
			}
			//displays an error message if the flag value is invalid
			else if (flag < 0 || flag > 1)
			{
				utilFunc.errorMessage(5, 0, 0);
				break;
			}
			//displays an error message if the t is unreachable from s
			else if (newGraph->array[s - 1].head == NULL)
			{
				printf("Sorry, node %d is not reachable from node %d\n", t, s);
				break;
			}
			//does dijkstra's algo if all conditions are met
			else
			{
				g.dijkstraSP(newGraph, s, t, flag);
				break;
			}

		case '\n':
			break;

		//prints an error message if an invalid value is entered
		default:
			printf("COMMAND: %c\n", c);
			printf("Invalid command.\n");
			break;
		}
	}
	getchar();
}
