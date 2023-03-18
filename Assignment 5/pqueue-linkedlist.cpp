/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */

#include <iostream>
#include "pqueue-linkedlist.h"
#include "error.h"


LinkedListPriorityQueue::LinkedListPriorityQueue() {
	first = NULL;
	listSize = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (first != NULL) {
		Node* next = first->next;
		delete first;
		first = next;
	}
}

int LinkedListPriorityQueue::size() {
	return listSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return listSize == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = NULL;

	if (first == NULL) { // if list is empty
		first = newNode;
	} else {
		Node* index = first; // for iteration

		for (Node* curr = first; curr != NULL; curr = curr->next) { // assigns index first node with value less than new one
			if (curr->value < value) {
				index = curr;
			} else break;
		}

		if (index == first) { // if only first node was such, determine position of new node, left or right
			if (first->value >= value) {
				newNode->next = first;
				first = newNode;
			} else {
				newNode->next = first->next;
				first->next = newNode;
			}
		} else { // insert new node in correct position
			newNode->next = index->next;
			index->next = newNode;
		}
	}

	listSize += 1;
}

string LinkedListPriorityQueue::peek() {
	if (isEmpty()) error("Queue is empty.");
	return first->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	string firstValue = peek();

	Node* second = first->next;
	delete first;
	first = second;

	listSize -= 1;
	return firstValue;
}

