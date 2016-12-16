#pragma once
#include "RBTree.h"

class Board{
private:
	RBTree *tree;
	int hashFunc(int x, int y);
public:
	bool checkPoint(int x, int y);
	void addPoint(int x, int y);
	Board();
	~Board();
};

