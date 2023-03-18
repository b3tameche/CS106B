/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */

#include <iostream>
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	first = NULL;
	listSize = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (first != NULL) {
		Node* second = first->next;
		delete first;
		first = second;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return listSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return listSize == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Node* newNode = new Node;
	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = first;

	if (first != NULL) { // if first node exists, link it to new node
		first->prev = newNode;
	}

	first = newNode;

	listSize += 1;
}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()) error("Queue is empty.");

	string result = first->value;
	for (Node* curr = first->next; curr != NULL; curr = curr->next) {
		if (curr->value < result) {
			result = curr->value;
		} // here we don't have else case since the list is unsorted
	}

	return result;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) error("Queue is empty.");

	string lowest = first->value;
	Node* index = first;

	for (Node* curr = first; curr != NULL; curr = curr->next) { // retrieve node with min value
		if (curr->value < lowest) {
			lowest = curr->value;
			index = curr;
		}
	}

	if (index == first) { // first node
		Node* second = first->next;
		delete first;
		first = second;
	} else if (index->next == NULL){ // last node
		index->prev->next = NULL;
		delete index;
	} else { // somewhere between
		Node* prev = index->prev;
		Node* next = index->next;
		delete index;
		prev->next = next;
		next->prev = prev;
	}

	listSize -= 1;

	return lowest;
}

