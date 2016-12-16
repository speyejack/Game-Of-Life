#pragma once
struct ListNode {
	ListNode *n;
	int pos[2];
};

class Queue {
private:
	ListNode *first;
	ListNode *last;
public:
	void queue(int pos[2]);
	int * dequeue();
	bool contains(int pos[2]);
	ListNode * getFirst();
	~Queue();
};
