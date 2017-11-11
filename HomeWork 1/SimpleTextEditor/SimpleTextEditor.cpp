// SimpleTextEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "stack"
#include "string"

using namespace std;

int main()
{
	stack<char> q1;
	stack<char> stk = q1;
	stack<char> stk1;
	int n, x = 0, k, k1, l = 0;
	cin >> n;
	string arr = "";
	int* commands = new int[n + 1];
	while (n != 0)
	{
		commands[l] = x;
		l++;
		cin >> x;
		if (x == 1)
		{
			cin >> arr;
			int i = 0;
			while (arr[i] != '\0')
			{
				q1.push(arr[i]);
				i++;
			}
		}
		if (x == 2)
		{
			cin >> k;
			for (int i = 0; i < k; i++)
			{
				stk.push(q1.top());
				q1.pop();
			}
		}
		if (x == 3)
		{
			cin >> k1;
			stk1 = q1;
			for (int i = 0; i < stk1.size() - k1; i++)
			{
				stk1.pop();
			}
			cout << stk1.top() << endl;
		}
		if (x == 4)
		{
			while (commands[l] == 3)
			{
				l--;
			}
			if (commands[l] == 1)
			{
				for (int i = 0; i < arr.length(); i++)
				{
					q1.pop();
				}
			}
			if (commands[l] == 2)
			{
				for (int i = 0; i < k; i++)
				{
					q1.push(stk.top());
					stk.pop();
				}
			}

		}
		n--;
	}
	return 0;
}

