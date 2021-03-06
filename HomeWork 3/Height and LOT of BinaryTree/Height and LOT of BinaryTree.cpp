// Height and LOT of BinaryTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "queue"

using namespace std;

template <class T>
struct node
{
	T inf;
	node<T> *left, *right;
};

template <class T>
class BinTree
{
private:
	node<T> *root;
	void DeleteBinTree(node<T>* &) const;
	void Copy(node<T>* &, node<T>* const&) const;
	void CopyBinTree(BinTree<T> const&);
	void pr(const node<T>*) const;
	void CreateBinTree(node<T>* &) const;
public:
	BinTree();
	~BinTree();
	BinTree(BinTree<T> const&);
	BinTree& operator = (BinTree<T> const&);
	T RootBinTree() const;
	BinTree<T>& LeftBinTree() const;
	BinTree<T>& RightBinTree() const;
	node<T>* GetRoot();
	bool empty() const;
	void print() const;
	void Create();
	void Create3(T, BinTree<T>, BinTree<T>);
};

template <typename T>
BinTree<T>::BinTree()
{
	root = NULL;
}

template <typename T>
BinTree<T>::~BinTree()
{
	DeleteBinTree(root);
}

template <typename T>
BinTree<T>::BinTree(BinTree<T> const& r)
{
	CopyBinTree(r);
}

template <typename T>
BinTree<T>& BinTree<T>::operator=(BinTree<T> const& r)
{
	if (this != &r)
	{
		DeleteBinTree(root);
		CopyBinTree(r);
	}
	return *this;
}

template <typename T>
void BinTree<T>::DeleteBinTree(node<T>* &p) const
{
	if (p)
	{
		DeleteBinTree(p->left);
		DeleteBinTree(p->right);
		delete p;
		p = NULL;
	}
}

template <typename T>
void BinTree<T>::CopyBinTree(BinTree<T> const& r)
{
	Copy(root, r.root);
}

template <typename T>
void BinTree<T>::Copy(node<T> * &pos, node<T>* const& r) const
{
	pos = NULL;
	if (r)
	{
		pos = new node<T>;
		pos->inf = r->inf;
		Copy(pos->left, r->left);
		Copy(pos->right, r->right);
	}
}

template <typename T>
bool BinTree<T>::empty() const
{
	return root == NULL;
}

template <typename T>
T BinTree<T>::RootBinTree() const
{
	return root->inf;
}

template <typename T>
node<T>* BinTree<T>::GetRoot()
{
	return root;
}

template <typename T>
BinTree<T>& BinTree<T>::LeftBinTree() const
{
	BinTree<T> t;
	Copy(t.root, root->left);
	return t;
}

template <typename T>
BinTree<T>& BinTree<T>::RightBinTree() const
{
	BinTree<T> t;
	Copy(t.root, root->right);
	return t;
}

template <typename T>
void BinTree<T>::pr(const node<T>*p) const
{
	if (p)
	{
		pr(p->left);
		cout << p->inf << " ";
		pr(p->right);
	}
}

template <typename T>
void BinTree<T>::print() const
{
	pr(root);
}

template <typename T>
void BinTree<T>::Create3(T x, BinTree<T> l, BinTree<T> r)
{
	root = new node<T>;
	root->inf = x;
	Copy(root->left, l.root);
	Copy(root->right, r.root);
}

template <typename T>
void BinTree<T>::CreateBinTree(node<T>* &pos) const
{
	T x; char c;
	cout << "root: ";
	cin >> x;
	pos = new node<T>;
	pos->inf = x;
	pos->left = NULL;
	pos->right = NULL;

	cout << "left BinTree of: " << x << " y/n? ";
	cin >> c;
	if (c == 'y') CreateBinTree(pos->left);
	cout << "right BinTree of: " << x << " y/n? ";
	cin >> c;
	if (c == 'y') CreateBinTree(pos->right);
}

template <typename T>
void BinTree<T>::Create()
{
	CreateBinTree(root);
}

template <typename T>
int height(node<T>* r)
{
	if (r == NULL) return -1;
	int n, m;
	n = height(r->left);
	m = height(r->right);
	if (n > m) return n + 1;
	return m + 1;
}

template <typename T>
void levelOrder(node<T>* p)
{
	queue<node<T>*> q;
	node<T>* temp = p;
	if (temp != NULL)
	{
		q.push(temp);
	}
	while (!q.empty())
	{
		cout << temp->inf << " ";
		if (temp->left != NULL) q.push(temp->left);
		if (temp->right != NULL) q.push(temp->right);
		q.pop();
		if (!q.empty()) temp = q.front();
	}
}

int main()
{
	BinTree<int> binTree;
	binTree.Create();
	binTree.print();
	cout << endl << height(binTree.GetRoot()) << endl;
	levelOrder(binTree.GetRoot());
	cout << endl;
	return 0;
}
