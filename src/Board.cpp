#include "stdafx.h"
#include "Board.h"
#include "RBTree.h"

int Board::hashFunc(int x, int y) {
	int comb = x + y;
	return comb * (comb + 1) / 2 + y;
}

bool Board::checkPoint(int x, int y) {
	return tree->contains(hashFunc(x, y));
}

void Board::addPoint(int x, int y) {
	tree->insert(hashFunc(x, y));
}

Board::Board(){
	tree = new RBTree();
}

Board::~Board(){
	delete tree;
}
