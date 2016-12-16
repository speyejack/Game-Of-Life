#include "stdafx.h"
#include "RBTree.h"
#define BLACK 0
#define RED 1


TreeNode * RBTree::grandparent(TreeNode *n) {
	if (n->parent == NULL || n->parent->parent == NULL) {
		return NULL;
	}
	else {
		return n->parent->parent;
	}
}

TreeNode * RBTree::uncle(TreeNode *n) {
	TreeNode *gpa = grandparent(n);
	if (gpa == NULL) 
		return NULL;

	if (gpa->left == n->parent)
		return gpa->right;
	else
		return gpa->left;
}

void RBTree::rotateLeft(TreeNode *root) {
	TreeNode *pivot = root->right;
	root->right = pivot->left;
	if (root->right != NULL)
		root->right->parent = root;
	pivot->left = root;
	pivot->parent = root->parent;
	if (pivot->parent == NULL)
		rootTree = pivot;
	root->parent = pivot;
}

void RBTree::rotateRight(TreeNode *root) {
	TreeNode *pivot = root->left;
	root->left = pivot->right;
	if (root->left != NULL)
		root->left->parent = root;
	pivot->right = root;
	pivot->parent = root->parent;
	if (pivot->parent == NULL)
		rootTree = pivot;
	root->parent = pivot;

}

void RBTree::insert(int num) {
	TreeNode *n = new TreeNode();
	n->color = RED;
	n->value = num;
	TreeNode *index = rootTree;
	if (rootTree == NULL)
		rootTree = n;
	else {
		while (true) {
			if (num > index->value) {
				if (index->right == NULL) {
					index->right = n;
					n->parent = index;
					break;
				} else {
					index = index->right;
				}
			} else {
				if (index->left == NULL) {
					index->left = n;
					n->parent = index;
					break;
				}
				else {
					index = index->left;
				}

			}

		}
	}
	insert_case1(n);
}

void RBTree::insert_case1(TreeNode *n) {
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(n);
}

void RBTree::insert_case2(TreeNode *n) {
	if (n->parent->color == BLACK)
		return;
	else
		insert_case3(n);
}

void RBTree::insert_case3(TreeNode *n) {
	TreeNode * u = uncle(n);
	if ((u != NULL) && (u->color == RED)) {
		n->parent->color = BLACK;
		u->color = BLACK;
		TreeNode * g = grandparent(n);
		g->color = RED;
		insert_case1(n);
	} else {
		insert_case4(n);
	}
}

void RBTree::insert_case4(TreeNode *n) {
	TreeNode * g = grandparent(n);
	if (g == NULL)
		return;
	if ((n == n->parent->right) && (n->parent == g->left)) {
		rotateLeft(n->parent);
		n = n->left;
	} else if ((n == n->parent->left) && (n->parent == g->right)) {
		rotateRight(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

void RBTree::insert_case5(TreeNode *n) {
	TreeNode *g = grandparent(n);
	n->parent->color = BLACK;
	g->color = RED;
	if (n == n->parent->left)
		rotateRight(g);
	else
		rotateLeft(g);
}

bool RBTree::contains(int num) {
	TreeNode *index = rootTree;
	while (index != NULL) {
		if (num == index->value)
			return true;
		if (num > index->value)
			index = index->right;
		else
			index = index->left;
	}
	return false;
}

RBTree::RBTree(){

}

RBTree::~RBTree(){
	delete rootTree;
}
