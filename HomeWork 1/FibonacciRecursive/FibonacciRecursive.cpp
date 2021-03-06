// FibonacciRecursive.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

using namespace std;

int FibOn2(int n)
{
	if (n <= 1)
		return n;
	else
		return FibOn2(n - 1) + FibOn2(n - 2);
}

int fibOn(int term, int val, int prev)
{
	if (term == 0) return prev;
	if (term == 1) return val;
	return fibOn(term - 1, val + prev, val);
}

void multiply(int F[2][2], int M[2][2])
{
	int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
	int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
	int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
	int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

	F[0][0] = x;
	F[0][1] = y;
	F[1][0] = z;
	F[1][1] = w;
}

void power(int F[2][2], int n)
{
	if (n == 0 || n == 1)
		return;
	int M[2][2] = { { 1,1 },{ 1,0 } };

	power(F, n / 2);
	multiply(F, F);

	if (n % 2 != 0)
		multiply(F, M);
}

int fibOlogn(int n)
{
	int F[2][2] = { { 1,1 },{ 1,0 } };
	if (n == 0)
		return 0;
	power(F, n - 1);

	return F[0][0];
}

int main()
{
	int n;
	cin >> n;
	cout << FibOn2(n) << endl;
	cout << fibOn(n, 1, 0) << endl;
	cout << fibOlogn(n) << endl;
	return 0;
}

