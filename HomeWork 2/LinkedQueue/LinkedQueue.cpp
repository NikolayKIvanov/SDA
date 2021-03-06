// LinkedQueue.cpp : Defines the entry point for the console application.
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
class LQueue
{
private:
	node<T> *front, *back;
	void copy(LQueue<T> const& q)
	{
		back = NULL;
		if (!q.empty())
		{
			node<T>* p = q.front;
			while (p)
			{
				push(p->data);
				p = p - next;
			}
		}
	}
	void clean()
	{
		while (!empty())
			pop();
	}
public:
	LQueue() : front(NULL), back(NULL) {}
	LQueue(LQueue<T> const& q) : front(NULL), back(NULL)
	{
		copy(q);
	}
	~LQueue()
	{
		clean();
	}
	bool empty() const
	{
		return back == NULL;
	}
	void push(T const& x)
	{
		node<T>* p = new node<T>;
		p->data = x;
		p->next = NULL;
		if (!empty())
		{
			back->next = p;
		}
		else
		{
			front = p;
		}
		back = p;
	}
	T pop()
	{
		if (empty())
		{
			cerr << "Empty Queue!\n";
			return T();
		}
		node<T>* p = front;
		T x = p->data;
		if (p == back)
		{
			front = NULL;
			back = NULL;
		}
		else
		{
			front = p->next;
		}
		delete p;
		return x;
	}
	T head() const
	{
		if (empty())
		{
			cerr << "Empty Queue!\n";
			return T();
		}
		return front->data;
	}
	void print()
	{
		node<T>* p = front;
		while (p)
		{
			cout << p->data << " ";
			p = p->next;
		}
	}
};

int main()
{
    return 0;
}

