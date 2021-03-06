// TrueGraph.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "iostream"
#include "cassert"
#include "queue"
#include "fstream"
#include "sstream"
#include "string"

using namespace std;

template <typename T>
struct elem_link1
{
	T inf;
	elem_link1<T>* link;
};

template <typename T>
class LList
{
private:
	elem_link1<T> *start, *end, *current;
	void deleteList();
	void copyList(LList const &);
public:
	LList();
	~LList();
	LList(LList const &);
	LList& operator= (LList const &);

	void iterStart(elem_link1<T> *p = NULL);
	elem_link1<T>* iter();

	bool empty() const;
	void toEnd(T const &);
	void insertAfter(elem_link1<T>*, T const &);
	void insertBefore(elem_link1<T>*, T const &);
	bool deleteAfter(elem_link1<T>*, T&);
	bool deleteBefore(elem_link1<T>*, T&);
	void deleteElem(elem_link1<T>*, T&);
	void print() const;
	int lenght() const;
	void concat(const LList&);
	void reverse();
};

template <typename T>
LList<T>::LList()
{
	start = NULL;
	end = NULL;
}

template <typename T>
LList<T>::~LList()
{
	deleteList();
}

template <typename T>
LList<T>::LList(const LList<T>& list)
{
	copyList(list);
}

template <typename T>
LList<T>& LList<T>::operator=(const LList<T>& list)
{
	if (this != &list)
	{
		deleteList();
		copyList(list);
	}
	return *this;
}

template <typename T>
void LList<T>::deleteList()
{
	elem_link1<T> *p;
	while (start)
	{
		p = start;
		start = start->link;
		delete p;
	}
	end = NULL;
}

template <typename T>
void LList<T>::copyList(LList<T> const & list)
{
	start = end = current = NULL;
	elem_link1<T> *p = list.start;
	while (p)
	{
		toEnd(p->inf);
		p = p->link;
	}
}

template <typename T>
void LList<T>::iterStart(elem_link1<T> *p)
{
	if (p) current = p;
	else current = start;
}

template <typename T>
elem_link1<T>* LList<T>::iter()
{
	elem_link1<T> *p = current;
	if (current) current = current->link;
	return p;
}

template <typename T>
void LList<T>::toEnd(T const & x)
{
	current = end;
	end = new elem_link1<T>;
	assert(end != NULL);
	end->inf = x;
	end->link = NULL;
	if (current) current->link = end;
	else start = end;
}

template <typename T>
void LList<T>::insertAfter(elem_link1<T> *p, T const & x)
{
	elem_link1<T> *q = new elem_link<T>;
	assert(q != NULL);
	q->inf = x;
	q->link = p->link;
	if (p == end) end = q;
	p->link = q;
}

template <typename T>
void LList<T>::insertBefore(elem_link1<T> *p, T const & x)
{
	elem_link1<T>* q = new elem_link1<T>;
	assert(q != NULL);
	*q = *p;
	if (p == end) end = q;
	p->inf = x;
	p->link = q;
}

template <typename T>
bool LList<T>::deleteAfter(elem_link1<T>* p, T& x)
{
	if (p->link)
	{
		elem_link1<T> *q = p->link;
		x = q->inf;
		p->link = q->link;
		if (q == end) end = p;
		delete q;
		return 1;
	}
	return 0;
}

template <typename T>
void LList<T>::deleteElem(elem_link1<T>* p, T& x)
{
	if (p == start)
	{
		x = p->inf;
		if (start == end)
		{
			start = end = NULL;
		}
		else start = start->link;
		delete p;
	}
	else
	{
		elem_link1<T>* q = start;
		while (q->link != p) q = q->link;
		deleteAfter(q, x);
	}
}

template <typename T>
bool LList<T>::deleteBefore(elem_link1<T>* p, T& x)
{
	if (p != start)
	{
		elem_link1<T> *q = start;
		while (q->link != p) q = q->link;
		deleteElem(q, x);
		return 1;
	}
	return 0;
}

template <typename T>
bool LList<T>::empty() const
{
	return start == NULL;
}

template <typename T>
void LList<T>::print() const
{
	elem_link1<T> *p = start;
	while (p)
	{
		cout << p->inf << " ";
		p = p->link;
	}
	cout << endl;
}

template <typename T>
int LList<T>::lenght() const
{
	int n = 0;
	elem_link1<T> *p = start;
	while (p)
	{
		n++;
		p = p->link;
	}
	return n;
}

template <typename T>
void LList<T>::concat(const LList<T>& r)
{
	elem_link1<T> *p = r.start;
	while (p)
	{
		toEnd(p->inf);
		p = p->link;
	}
}

template <typename T>
void LList<T>::reverse()
{
	LList<T> r;
	iterStart();
	elem_link1<T> *p = iter();
	if (p)
	{
		r.toEnd(p->inf);
		p = p->link;
		while (p)
		{
			r.insertBefore(r.start, p->inf);
			p = p->link;
		}
	}
	*this = r;
}

typedef LList<int> IntList;
typedef LList<IntList> IntGraph;

template <typename T>
class graph
{
public:
	void addTop(const T&);
	void deleteTop(const T&);
	void addRib(const T&, const T&);
	void deleteRib(const T&, const T&);
	bool top(const T&);
	bool rib(const T&, const T&);
	bool empty() const;
	elem_link1<T>* point(const T&);
	LList<T> vertexes();
	void print();
private:
	LList<LList<T>> g;
};

template<typename T>
bool graph<T>::empty() const
{
	return g.empty();
}
template <typename T>
void graph<T>::addTop(const T& a)
{
	LList<T> l;
	l.toEnd(a);
	g.toEnd(l);
}

template <typename T>
void graph<T>::deleteTop(const T& a)
{
	g.iterStart();
	elem_link1<LList<T>>* p = g.iter(), *r;
	while (p)
	{
		p->inf.iterStart();
		elem_link1<T>* q = p->inf.iter();
		if (rib(q->inf, a)) deleteRib(q->inf, a);
		p = p->link;
	}
	g.iterStart();
	elem_link1<T>* q;
	do
	{
		r = g.iter();
		r->inf.iterStart();
		q = r->inf.iter();
	} while (q->inf != a);
	LList<T> x;
	g.deleteElem(r, x);
}

template <typename T>
void graph<T>::addRib(const T& a, const T& b)
{
	elem_link1<T>* q = point(a), *p;
	p = new elem_link1<T>;
	assert(p != NULL);
	p->inf = b;
	p->link = q->link;
	q->link = p;
}

template <typename T>
void graph<T>::deleteRib(const T& a, const T& b)
{
	g.iterStart();
	elem_link1<LList<T>>* p;
	elem_link1<T> *q;
	do
	{
		p = g.iter();
		p->inf.iterStart();
		q = p->inf.iter();
	} while (q->inf != a);
	q = q->link;
	while (q->inf != b) q = q->link;
	T x;
	p->inf.deleteElem(q, x);
}

template <typename T>
bool graph<T>::top(const T& a)
{
	if (g.empty()) return false;
	g.iterStart();
	elem_link1<LList<T>> *p = g.iter();
	elem_link1<T> *q;
	do
	{
		p->inf.iterStart();
		q = p->inf.iter();
		p = p->link;
	} while (q->inf != a && p);
	return q->inf == a;
}

template <typename T>
bool graph<T>::rib(const T& a, const T& b)
{
	elem_link1<T>* p = point(a);
	p = p->link;
	while (p && p->inf != b) p = p->link;
	return p != NULL;
}

template <typename T>
elem_link1<T>* graph<T>::point(const T& a)
{
	g.iterStart();
	elem_link1<LList<T>> * p;
	elem_link1<T>* q;
	do
	{
		p = g.iter();
		p->inf.iterStart();
		q = p->inf.iter();
	} while (q->inf != a);
	return q;
}

template <typename T>
LList<T> graph<T>::vertexes()
{
	LList<T> l;
	g.iterStart();
	elem_link1<LList<T>>* p = g.iter();
	do
	{
		p->inf.iterStart();
		elem_link1<T> *q = p->inf.iter();
		l.toEnd(q->inf);
		p = p->link;
	} while (p);
	return l;
}

template <typename T>
void graph<T>::print()
{
	g.iterStart();
	elem_link1<LList<T>> * p = g.iter();
	while (p)
	{
		p->inf.print();
		p = p->link;
	}
	cout << endl;
}

template <typename T>
void create_graph(graph<T> &g)
{
	char c;
	do
	{
		cout << "top_of_graph: ";
		int x; cin >> x;
		addTop(x);
		cout << "Top y/n? "; cin >> c;
	} while (c == 'y');

	cout << "Ribs:\n";

	do
	{
		cout << "start top: ";
		int x; cin >> x;
		cout << "end top: ";
		int y; cin >> y;
		addRib(x, y);
		cout << "next: y/n? "; cin >> c;
	} while (c == 'y');
}

template <typename T>
void BFS(const T& a, graph<T>& g, LList<T>& l, LList<T>& temp)
{
	queue<T> q; q.push(a);
	l.toEnd(a);
	int count = 0;
	while (!q.empty())
	{
		T x; x = q.front();
		q.pop();
		elem_link1<T>* p = g.point(x);
		p = p->link;
		count++;
		while (p)
		{
			if (!member(p->inf, l))
			{
				q.push(p->inf);
				l.toEnd(p->inf);
			}
			else if (count == 4)
			{
				count = 0;
				temp.toEnd(p->inf);
			}
			p = p->link;
		}
	}
	temp.print();
}

template <typename T>
bool member(const T& a, LList<T> l)
{
	l.iterStart();
	elem_link1<T>* p = l.iter();
	while (p && p->inf != a) p = p->link;
	return p != NULL;
}

const int SIZE = 100;

void parse(char x[], int& j, int nums[SIZE])
{
	string temp = x;
	stringstream ss(temp);
	int i = 0;
	while (ss)
	{
		ss >> nums[i++];
	}
	j = i - 1;
}

template <typename T>
void createGraph(graph<T>& g, ifstream& text)
{
	text.open("test.txt");
	LList<T> l;
	while (!text.eof())
	{
		int j = 0;
		int nums[SIZE];
		char x[SIZE];
		text.getline(x, SIZE);
		parse(x, j, nums);
		int i = 0;
		if (!member(nums[i], l))
		{
			l.toEnd(nums[i]);
			g.addTop(nums[i]);
		}
		i++;
		while (i < j)
		{
			if (!member(nums[i], l))
			{
				l.toEnd(nums[i]);
				g.addTop(nums[i]);
			}
			g.addRib(nums[0], nums[i++]);
		}
	}
	text.close();
}

void NumOfGardens(graph<int>& g)
{
	LList<int> final1;
	for (int i = 1; i <= 8; i++)
	{
		LList<int> l, l1;
		BFS(i, g, l, l1);
		l1.iterStart();
		elem_link1<int>* p = l1.iter();
		while (p)
		{
			if (!member(p->inf, final1)) final1.toEnd(p->inf);
			p = p->link;
		}
	}
	cout << final1.lenght() << endl;
}
void readMatrix(int& N, int matrix[20][20])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> matrix[i][j];
		}
	}
}
void GraphFromMatrix(int& N, int matrix[20][20], graph<int>& g)
{
	LList<int> l;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] == 1)
			{
				if (!member(i + 1, l))
				{
					l.toEnd(i + 1);
					g.addTop(i + 1);
				}
				if (!member(j + 1, l))
				{
					l.toEnd(j + 1);
					g.addTop(j + 1);
				}
				g.addRib(i + 1, j + 1);
			}
		}
	}
}
int main()
{
	graph<int> g1, g;
	ifstream text;
	createGraph(g1, text);
	int matrix[20][20], N;
	cin >> N;
	readMatrix(N, matrix);
	GraphFromMatrix(N, matrix, g);
	g.print();
	g1.print();
	NumOfGardens(g);
	NumOfGardens(g1);
	return 0;
}

