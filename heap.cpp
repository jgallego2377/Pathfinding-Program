#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include<iostream>
#include<set>
#include<list>
#include<algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"
#include "graph.h"

using namespace std;

//creates a new heap node
struct minHeapNode* heap::newMinHeapNode(int i, int cost)
{
	//dynamically allocates memory for the node
	struct minHeapNode* minHeapNode = (struct minHeapNode*)malloc(sizeof(struct minHeapNode));

	//sets the location of the node and the cost of the node
	minHeapNode->i = i;
	minHeapNode->cost = cost;

	//returns the node
	return minHeapNode;
}

//creates the min heap
struct minHeap* heap::createMinHeap(int capacity)
{
	//dynamically allocates memory for the heap
	struct minHeap* minHeap = (struct minHeap*)malloc(sizeof(struct minHeap));

	//sets the position, size, capcity and allocates memory
	minHeap->position = (int *)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct minHeapNode**)malloc(capacity * sizeof(struct minHeapNode*));

	//returns the heap
	return minHeap;
}

//swaps two nodes
void heap::swapMinHeapNodes(struct minHeapNode** a, struct minHeapNode** b)
{
	//swaps node a with node b
	struct minHeapNode* temp = *a;
	*a = *b;
	*b = temp;
}

//rearranges the heap into a min heap
void heap::minHeapify(struct minHeap* minHeap, int i)
{
	//creates a three variables for the algorithm
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	//checks to see if the heap is violated on the left side
	if (left < minHeap->size && minHeap->array[left]->cost < minHeap->array[smallest]->cost)
		smallest = left;

	//checks to see if the heap is violated on the right side
	if (right < minHeap->size && minHeap->array[right]->cost < minHeap->array[smallest]->cost)
		smallest = right;

	//checks to see if the smallest is equal or not to the new value
	if (smallest != i)
	{
		//creates two nodes that point to the smallest node in the heap
		//and the new node in the heap
		minHeapNode *smallestNode = minHeap->array[smallest];
		minHeapNode *idNode = minHeap->array[i];

		//swaps the positions of these two nodes
		minHeap->position[smallestNode->i] = i;
		minHeap->position[idNode->i] = smallest;

		//swaps the two nodes
		swapMinHeapNodes(&minHeap->array[smallest], &minHeap->array[i]);

		//reorganizes the heap
		minHeapify(minHeap, smallest);
	}
}

//checks to see if the heap is empty
int heap::isEmpty(struct minHeap* minHeap)
{
	return minHeap->size == 0;
}

//removes the smallest element of the heap
struct minHeapNode* heap::extractMin(struct minHeap* minHeap)
{
	//returns null if the heap is empty
	if (isEmpty(minHeap))
		return NULL;

	//creates a minheapnode that points to the top of the heap
	struct minHeapNode* root = minHeap->array[0];
	//creates a minheapnode that points to the last node of the heap
	struct minHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	
	//the last node of the heap becomes the new top node of the heap
	minHeap->array[0] = lastNode;

	//swaps positions of the first & last ndoes of the heap
	minHeap->position[root->i] = minHeap->size - 1;
	minHeap->position[lastNode->i] = 0;

	//decrements the heap size
	minHeap->size--;
	//reorganizes the heap to ensure it is a min heap
	minHeapify(minHeap, 0);

	//returns the root node
	return root;
}

//decreases the key of a node in the heap
void heap::decreaseKey(struct minHeap* minHeap, int v, int dist)
{
	//i copies the position of the node at location v
	int i = minHeap->position[v];
	//changes the value of cost according to the variable dist
	minHeap->array[i]->cost = dist;

	//loops while the cost of the child is less than the parents
	while (i && minHeap->array[i]->cost < minHeap->array[(i - 1) / 2]->cost)
	{
		//swaps positions with the two nodes
		minHeap->position[minHeap->array[i]->i] = (i - 1) / 2;
		minHeap->position[minHeap->array[(i - 1) / 2]->i] = i;
		//swaps nodes
		swapMinHeapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
		//i becomes its parent
		i = (i - 1) / 2;
	}
}

//checks to see if the value is in the heap
bool heap::isInMinHeap(struct minHeap *minHeap, int v)
{
	//returns true if it is in the heap
	if (minHeap->position[v] < minHeap->size)
		return true;
	return false;
}
