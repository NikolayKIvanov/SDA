// MaxElStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

using namespace std;

template <typename T>
struct node
{
	T data;
	node* next;
};

template <typename T>
class LStack
{
private:
	node<T>* topNode;
	void copy(node<T>* toCopy); // Копиране на паметта на стека от друго място
	void eraseStack(); // Изтриване на паметта
	void copyStack(LStack const&); // Копиране на стека
public:
	LStack();							//
	LStack(LStack const&);				// Голяма четворка
	LStack& operator=(LStack const&);	//
	~LStack();							//

	bool empty() const;
	void push(T const& x);
	T pop();
	T top() const;
};
const int INITIAL = 16;

template <typename T>
LStack<T>::LStack() : topNode(nullptr) {}

template <typename T>
bool LStack<T>::empty() const
{
	return topNode == nullptr;
}

template <typename T>
T LStack<T>::pop()
{
	if (empty())
	{
		cerr << "празен стек!\n";
		return 0;
	}
	node<T>* p = topNode;
	topNode = topNode->next;
	T x = p->data;
	delete p;
	return x;
}

template <typename T>
T LStack<T>::top() const
{
	if (empty())
	{
		cerr << "празен стек!\n";
		return 0;
	}
	return topNode->data;
}

template <typename T>
void LStack<T>::eraseStack()
{
	while (!empty())
		pop();
}

template <typename T>
LStack<T>::~LStack()
{
	eraseStack();
}

template <typename T>
void LStack<T>::push(T const& x)
{
	node<T>* p = new node<T>;
	p->data = x;
	p->next = topNode;
	topNode = p;
}

template <typename T>
void LStack<T>::copy(node<T>* toCopy)
{
	if (toCopy == nullptr)
		return;
	copy(toCopy->next);
	push(toCopy->data); //добавяме първия елемент отгоре
}

template <typename T>
void LStack<T>::copyStack(LStack const& ls)
{
	topNode = nullptr;
	copy(ls.topNode);
}

template <typename T>
LStack<T>::LStack(LStack const& ls)
{
	copyStack(ls);
}

template <typename T>
LStack<T>& LStack<T>::operator=(LStack const& ls)
{
	if (this != &ls)
	{
		eraseStack();
		copyStack(ls);
	}
	return *this;
}

//int main()
//{
//	LStack<int> stk;
//	int n;
//	cin >> n;
//	int x,element;
//	while (n != 0)
//	{
//		cin >> x;
//		if (x == 1)
//		{
//			cin >> element;
//			stk.push(element);
//		}
//		else if (x == 2)
//		{
//			stk.pop();
//		}
//		else if (x == 3)
//		{
//			LStack<int> stkBuff = stk;
//			int maxEl = stkBuff.pop();
//			while (!stkBuff.empty())
//			{
//				if (maxEl <= stkBuff.top())
//				{
//					maxEl = stkBuff.pop();
//				}
//				else
//				{
//					stkBuff.pop();
//				}
//			}
//			cout << maxEl << endl;
//		}
//		n--;
//	}
//	return 0;
//}
int main()
{
	LStack<int> stk1, stk2;
	int n;
	cin >> n;
	int x, element;
	while (n != 0)
	{
		cin >> x;
		if (x == 1)
		{
			cin >> element;
			if (stk1.empty())
			{
				stk1.push(element);
				stk2.push(element);
			}
			else
			{
				stk1.push(element);
				if (element > stk2.top())
					stk2.push(element);
				else
					stk2.push(stk2.top());
			}
		}
		else if (x == 2)
		{
			stk1.pop();
			stk2.pop();
		}
		else if (x == 3)
		{
			cout << stk2.top() << endl;
		}
		n--;
	}
	return 0;
}


