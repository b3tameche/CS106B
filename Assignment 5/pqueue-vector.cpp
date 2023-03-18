/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	Vector<string> elems;
	elemsSize = 0;

}

VectorPriorityQueue::~VectorPriorityQueue() {

}

int VectorPriorityQueue::size() {
	return elemsSize;
}

bool VectorPriorityQueue::isEmpty() {
	return elemsSize == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	elems += value;
	elemsSize += 1;
}

string VectorPriorityQueue::peek() {
	if (elems.isEmpty()) error("Queue is empty.");
	string result = elems[0];
	foreach(string curr in elems) {
		if (curr < result) result = curr;
	}
	return result;
}

string VectorPriorityQueue::dequeueMin() {
	if (elems.isEmpty()) error("Queue is empty.");

	int index = 0;
	string result = elems[0];

	for (int i = 1; i < elems.size(); i++) {
		if (elems[i] < result) {
			index = i;
			result = elems[i];
		}
	}

	elems.remove(index);
	elemsSize -= 1;
	return result;
}

