// GameOfTwoStacks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "stack"

using namespace std;

void readArr(int n, stack<int> &stk)
{
	int *arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	for (int i = n - 1; i >= 0; i--)
	{
		stk.push(arr[i]);
	}
	delete[] arr;
}

int main()
{
	int g, n, m, x;
	cin >> g;
	stack<int> stkA, stkB;
	while (g != 0)
	{
		cin >> n >> m >> x;
		readArr(n, stkA);
		readArr(m, stkB);
		int CurrentSum = 0;
		int counter = 0;
		while (!stkA.empty() || !stkB.empty())
		{
			if (stkA.empty())
			{
				CurrentSum += stkB.top();
				if (x < CurrentSum)
					break;
				stkB.pop();
				counter++;
			}
			else if (stkB.empty())
			{
				CurrentSum += stkA.top();
				if (x < CurrentSum)
					break;
				stkA.pop();
				counter++;
			}
			else if (stkA.top() <= stkB.top())
			{
				CurrentSum += stkA.top();
				if (x < CurrentSum)
					break;
				stkA.pop();
				counter++;
			}
			else if (stkA.top() > stkB.top())
			{
				CurrentSum += stkB.top();
				if (x < CurrentSum)
					break;
				stkB.pop();
				counter++;
			}
		}
		cout << counter << endl;
		g--;
	}
	return 0;
}

