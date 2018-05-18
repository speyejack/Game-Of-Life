#include "Queue.h"
#include <iostream>

void Queue::queue(int pos[2]){
	//std::cout << pos[0] << ":" << pos[1]<<"\n";
	if (first == NULL) {
		first = last = new ListNode();
		last->pos[0] = pos[0];
		last->pos[1] = pos[1];
	}
	else {
		ListNode *temp = last;
		last = new ListNode();
		temp->n = last;
		last->pos[0] = pos[0];
		last->pos[1] = pos[1];

	}
}

int * Queue::dequeue() {
	int *tempVal;
	ListNode *tempRef = first;
	tempVal = first->pos;
	first = first->n;
	delete tempRef;
	return tempVal;
}

bool Queue::contains(int pos[2]) {
	if (first == NULL)
		return false;
	ListNode *n = first;
	while (n != NULL) {
		if ((n->pos[0] == pos[0]) && (n->pos[1] == pos[1]))
			return true;
		n = n->n;
	}
	return false;
}

Queue::~Queue() {
	while (first != NULL) {
		ListNode *temp = first;
		first = first->n;
		delete temp;
	}
}


ListNode * Queue::getFirst() {
	return first;
}

void Queue::write_to_stream(std::ostream& os){
	ListNode* n = first;
	os << "[";
	while (n != NULL){
		os << "{" << n->pos[0] << ", " << n->pos[1] << "},";
		n = n->n;
	}
	os << "]";
}

std::ostream& operator<<(std::ostream& os, Queue& q){
	q.write_to_stream(os);
	return os;
}
