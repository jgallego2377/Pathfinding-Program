#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "graph.h"
#include "heap.h"

//creates a fake infinity with the value of 100,000
#define INF 100000

//creates a new node for the adjacent list
struct AdjListNode* graph::newAdjListNode(int source, int dest, int weight)
{
	//dynamically allocates memory for the node
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	
	//sets the node's source, destination, weight and next node pointer
	newNode->source = source;
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;

	//returns the newly created node
	return newNode;
}

//creates a graph
struct Graph* graph::createGraph(int V, int E)
{
	//dynamically allocates memory for the graph
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));

	//sets the values of vertices & edges
	graph->V = V;
	graph->E = E;

	//dynamically allocates memory for the graph's array
	graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

	//sets all the pointers in the adj list to null
	for (int i = 0; i < V; ++i)
	{
		graph->array[i].head = NULL;
	}

	//returns the graph
	return graph;
}

//adds an edge to the graph
void graph::addEdge(struct Graph* graph, int source, int dest, int weight)
{
	//g is our graph
	class graph g;

	//creates a new adj list node with values (source, dest, and weight)
	struct AdjListNode* newNode = g.newAdjListNode(source, dest, weight);

	//creates a pointer of adjlistnode that points to the source value of the adj list
	AdjListNode *curr = graph->array[source].head;

	//adds the new edge at the beginning of the head if it was previously empty
	if (curr == NULL)
	{
		newNode->next = graph->array[source].head;
		graph->array[source].head = newNode;
	}
	//traverses the adj list to add the edge
	else
	{
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newNode;
	}

}

//prints the graph
void graph::printGraph(struct Graph* graph)
{
	//prints the vertices and edges specified in the text file
	printf("%d %d\n", graph->V, graph->E);

	//prints information on the graph's vertices
	for (int i = 0; i < graph->V; i++)
	{
		//creates a pointer of adjlistnode that points to the beginning of the adjacency list
		struct AdjListNode* ptr = graph->array[i].head;

		//prints the vertice
		printf("%d : ", i + 1);

		//loops while the pointer has a non-null value
		while (ptr)
		{
			//prints the destination of the current vertice and the weight from the source->dest
			printf("(%d, %d)", (ptr->dest + 1), ptr->weight);
			//prints a semicolon if there are still more values to print
			if (ptr->next != NULL)
			{
				printf("; ");
				ptr = ptr->next;
			}
			else
				//pointer points to the next location
				ptr = ptr->next;
		}
		//prints a new line
		printf("\n");
	}
}

//prints the path
void graph::printPath(int path[], int V, int end)
{
	if (path[V] == - 1)
		return;
	
	printPath(path, path[V], end);
	if (end == V - 1)
		printf("%d", V + 1);
	else
		printf("%d, ", V + 1);
}

//implements dijkstra's shortest path algorithm
void graph::dijkstraSP(struct Graph* graph, int source, int end, int flag)
{
	//h is our min heap
	heap h;

	//sets the integer V according to the vertices in the graph
	int V = graph->V;
	int *cost = new int[V]; //creates an array of size V that holds the finals costs of the vertices
	int *path = new int[V]; //creates an array of size V that holds the path from s->t

	//initializes all elements of the path array into -1
	for (int i = 0; i < V; i++)
		path[i] = -1;

	//creates a minheap depending on the vertices of the graph
	struct minHeap* minHeap = h.createMinHeap(V);
	
	//initializes all necessary components
	for (int i = 0; i < V; i++)
	{
		//sets the cost of all vertices equal to infinity
		cost[i] = INF;
		//sets new heap nodes in the heap
		minHeap->array[i] = h.newMinHeapNode(i, cost[i]);
		//sets new positions in the heap
		minHeap->position[i] = i;
	}

	//Note: source - 1 is used because we have vertices > 0 while arrays start at 0

	//updates the array and the position according to the source 
	minHeap->array[source - 1] = h.newMinHeapNode(source - 1, cost[source - 1]);
	minHeap->position[source - 1] = (source - 1);
	//sets the cost of the source equal to 0
	cost[source - 1] = 0;
	//reorganizes the heap according to the source
	h.decreaseKey(minHeap, (source - 1), cost[source - 1]);

	//sets the size of the heap equal to the amount of vertices
	minHeap->size = V;

	//loops while heap isn't empty
	while (!(h.isEmpty(minHeap)))
	{
		//takes the smallest value in the heap
		struct minHeapNode* minHeapNode = h.extractMin(minHeap);
		//int u holds the location of the smallest node in the heap
		int u = minHeapNode->i;

		//creates a pointer to the uth value of the adjacency list
		struct AdjListNode* ptr = graph->array[u].head;

		//loops while the adj list node pointer has a valid value
		while (ptr != NULL)
		{
			//int v holds the destination of the list
			int v = ptr->dest;
			
			//Relaxation of the edges
			if (ptr->weight + cost[u] < cost[v])
			{
				//updates the cost
				cost[v] = (cost[u] + ptr->weight);\
				//reorganizes the heap according to the new cost array
				h.decreaseKey(minHeap, v, cost[v]);
				//updates the path array
				path[v] = u;
			}
			//increments the pointer
			ptr = ptr->next;

		}
	}


	//Displays the length from s->t
	if (flag == 0)
	{
		//if the cost is infinite, that means that vertex was never visited
		if (cost[end - 1] == INF)
		{
			printf("Sorry, node %d is not reachable from node %d\n", end, source);
		}
		//prints the length needed to visit t from s
		else
		{
			printf("LENGTH: %d\n", cost[end - 1]);
		}
	
	}

	//Displays the path from s->t
	if (flag == 1)
	{
		//if the cost is infinite, that means that vertex was never visited
		if (cost[end - 1] == INF)
		{
			printf("Sorry, node %d is not reachable from node %d\n", end, source);
		}
		//prints a single path source if the start = finish
		else if (source == end)
		{
			printf("PATH: %d\n", source);
		}
		//prints the shortest route
		else
		{
			printf("PATH: %d, ", source);
			printPath(path, end - 1, end);
			printf("\n");
		}
	}

	//deletes the dynamically allocated arrays
	delete[] cost;
	delete[] path;
}
