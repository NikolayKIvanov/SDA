// QueueViaTwoStacks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "stack"

using namespace std;

class QueueS
{
private:
	stack<int> newStack, oldStack;
public:
	void push(int x)
	{
		newStack.push(x);
	}
	void pop()
	{
		if (oldStack.size() == 0)
		{
			while (!newStack.empty())
			{
				oldStack.push(newStack.top());
				newStack.pop();
			}
		}
		oldStack.pop();
	}
	int print()
	{
		if (oldStack.size() == 0)
		{
			while (!newStack.empty())
			{
				oldStack.push(newStack.top());
				newStack.pop();
			}
		}
		return oldStack.top();
	}
};


int main()
{
	QueueS q1;
	int n, number, x;
	cin >> number;
	while (number != 0)
	{
		cin >> n;
		if (n == 1)
		{
			cin >> x;
			q1.push(x);
		}
		if (n == 2)
		{
			q1.pop();
		}
		if (n == 3)
		{
			cout << q1.print() << endl;
		}
		number--;
	}
	return 0;
}

