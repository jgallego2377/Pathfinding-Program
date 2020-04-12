#pragma once
#ifndef HEAP_H_
#define HEAP_H_

struct minHeapNode {
	int i; //holds the location
	int cost; //holds the cost
};

struct minHeap {
	int size; //size of heap
	int capacity; //capacity of heap
	int *position; //helper variable for finding vertices
	struct minHeapNode **array; //helper variable for finding vertices
};

class heap {
public:
	struct minHeapNode* newMinHeapNode(int v, int dist);
	struct minHeap* createMinHeap(int capacity);
	void swapMinHeapNodes(struct minHeapNode** a, struct minHeapNode** b);
	void minHeapify(struct minHeap* minHeap, int idx);
	int isEmpty(struct minHeap* minHeap);
	struct minHeapNode* extractMin(struct minHeap* minHeap);
	void decreaseKey(struct minHeap* minHeap, int v, int dist);
	bool isInMinHeap(struct minHeap *minHeap, int v);

};

#endif // !HEAP_H_
