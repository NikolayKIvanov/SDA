
#include "iostream"
#include "string"

using namespace std;

template <class T>
struct node
{
	T inf;
	node<T> *left, *right;
};

bool checkBST(node<int>* root, node<int>* lefty, node<int>* righty)
{
	if (!root) return true;
	if (lefty && root->inf <= lefty->inf || righty && root->inf >= righty->inf) return false;
	return (checkBST(root->left, lefty, root) && checkBST(root->right, root, righty));
}

bool checkBST(node<int>* root)
{
	return checkBST(root, NULL, NULL);
}
