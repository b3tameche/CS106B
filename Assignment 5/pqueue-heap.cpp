/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	logicalLength = 0;
	allocatedLength = 8; // level of 3
	elems = new string[8];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] elems;
}

int HeapPriorityQueue::size() {
	return logicalLength;
}

bool HeapPriorityQueue::isEmpty() {
	return logicalLength == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	if (logicalLength == allocatedLength) { // if we need more space
		allocatedLength *= 2; // double the allocated space

		string* updated = new string[allocatedLength]; 
		for (int i = 0; i < logicalLength; i++) {
			updated[i] = elems[i]; // copy existed elements in new array
		}

		delete[] elems;
		elems = updated;
	}

	elems[logicalLength] = value; // last enqueued element in array
	logicalLength += 1;

	bubbleUp(logicalLength-1);
}

string HeapPriorityQueue::peek() {
	if (isEmpty()) error("Queue is empty");
	return elems[0];
}

string HeapPriorityQueue::dequeueMin() {
	string root = peek(); // peek() checks if array is empty

	string last = elems[logicalLength - 1];
	elems[0] = last; // root element becomes last enqueued element in array

	bubbleDown(0); // sorts elements
	logicalLength -= 1; // when sorting finishes size of enqueued elements gets shrinked by 1

	return root;
}

void HeapPriorityQueue::bubbleUp(int index) {
	if (index == 0) return; // if we reached root node
	if (elems[index] < elems[(index-1)/2]) { // division by 2 gives us floor of the actual result
		string child = elems[index];
		elems[index] = elems[(index-1)/2];
		elems[(index-1)/2] = child; // swap them
		bubbleUp((index-1)/2); // repeat same for new node
	}
}

void HeapPriorityQueue::bubbleDown(int index) {
	int cL = index*2 + 1; // left child index
	int cR = cL + 1; // right child index

	if (cL > logicalLength - 2) return; // if they're more than actual enqueued elements size (minus last element which is not needed anymore)

	/* get child with lower value using ternary, after some research, I found out that initial type and value for array 
	 * elements was string and "", so there would not be a problem if only cR would be more than actual enqueued elements size
	 */
	int lower = elems[cL] < elems[cR] ? cL : cR;

	if (elems[index] > elems[lower]) { // if we need to swap them
		string parent = elems[index];
		elems[index] = elems[lower];
		elems[lower] = parent;
		bubbleDown(lower);
	}
}