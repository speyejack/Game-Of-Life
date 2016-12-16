#pragma once
struct TreeNode {
	TreeNode * parent;
	TreeNode * left;
	TreeNode * right;
	bool color;
	int value;

	TreeNode() {
		parent = 0;
		left = 0;
		right = 0;
	}
	~TreeNode() {
		delete left;
		delete right;
	}
};

class RBTree{
private:
	TreeNode *rootTree;
	void rotateLeft(TreeNode *root);
	void rotateRight(TreeNode *root);
	TreeNode * grandparent(TreeNode *n);
	TreeNode * uncle(TreeNode *n);
	void insert_case1(TreeNode * n);
	void insert_case2(TreeNode * n);
	void insert_case3(TreeNode * n);
	void insert_case4(TreeNode * n);
	void insert_case5(TreeNode * n);
public:
	void insert(int num);
	bool contains(int num);
	RBTree();
	~RBTree();
};

