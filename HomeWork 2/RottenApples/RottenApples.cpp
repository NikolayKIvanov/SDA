// RottenApples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "queue"

using namespace std;

void readMatrix(int arr[][100], int n, int m)
{
	for (int i = 0; i <= n + 1; i++)
	{
		for (int j = 0; j <= m + 1; j++)
		{
			if (i == 0 || i == n + 1 || j == 0 || j == m + 1)
			{
				arr[i][j] = 0;
			}
			else cin >> arr[i][j];
		}
	}
}
void searchRotting(int arr[][100], int n, int m)
{
	queue<int*> temp;
	int counter = 0;
	for (int i = 0; i <= n + 1; i++)
	{
		for (int j = 0; j <= m + 1; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	while (true)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (arr[i][j] == 2 && arr[i - 1][j] == 1)
				{
					temp.push(&arr[i - 1][j]);
				}
				if (arr[i][j] == 2 && arr[i + 1][j] == 1)
				{
					temp.push(&arr[i + 1][j]);
				}
				if (arr[i][j] == 2 && arr[i][j - 1] == 1)
				{
					temp.push(&arr[i][j - 1]);
				}
				if (arr[i][j] == 2 && arr[i][j + 1] == 1)
				{
					temp.push(&arr[i][j + 1]);
				}
			}
		}
		for (int i = 0; i <= n + 1; i++)
		{
			for (int j = 0; j <= m + 1; j++)
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		if (temp.empty()) break;
		while (!temp.empty())
		{
			*temp.front() = 2;
			temp.pop();
		}
		counter++;
		cout << endl;
	}
	cout << counter << endl;
}
int main()
{
	int n, m;
	cin >> n >> m;
	int arr[100][100];
	readMatrix(arr, n, m);
	searchRotting(arr, n, m);
	return 0;
}

