#pragma once

#ifndef GRAPH_H_
#define GRAPH_H_

//AdjListNode is a node for the adjacency list
struct AdjListNode {
	int source; //holds the vertex source
	int dest; //holds the destination of the vertex
	int weight; //holds the weight from the source->destination
	struct AdjListNode* next; //holds a pointer to the next node
};

//AdjList creates the adjacency list
struct AdjList {
	struct AdjListNode *head; //holds a pointer of type adjlistnode
};

//Graph is made up of the adjacency list
struct Graph {
	int V; //V holds vertices
	int E; //E holds edges
	struct AdjList* array; //array is the adjacency list
};

class graph {
public:
	struct AdjListNode* newAdjListNode(int source, int dest, int weight);
	struct Graph* createGraph(int V, int E);
	void addEdge(struct Graph* graph, int source, int dest, int weight);
	void printGraph(struct Graph* graph);
	void dijkstraSP(struct Graph* graph, int source, int end, int flag);
	void printPath(int path2[], int i, int end);
};

#endif
