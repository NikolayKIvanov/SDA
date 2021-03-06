
#include "iostream"
#include "string"

using namespace std; 

template <class T>
struct node
{
	T inf;
	node<T> *left, *right;
};

void HuffmanDEC(node<char>* root, string s)
{
	string Decoded = "";
	int i = 0;
	node<char>* temp = root;
	while (i != s.length())
	{
		if (s[i] == '1')
		{
			root = root->right;
		}
		else if (s[i] == '0')
		{
			root = root->left;
		}
		if (!root->left && !root->right)
		{
			Decoded.push_back(root->inf);
			root = temp;
		}
		i++;
	}
	cout << Decoded << endl;
}
