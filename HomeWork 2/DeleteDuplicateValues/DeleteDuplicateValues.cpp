// DeleteDuplicateValues.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "assert.h"

using namespace std;

template <typename T = int>
struct elem_link1
{
	T inf;
	elem_link1<T>* link;
};

template <typename T = int>
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
	elem_link1<T>* getEnd() const
	{
		return end;
	}
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
	return this*;
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
		p = p->link
			while (p)
			{
				r.insertBefore(r.start, p->inf);
				p = p->link;
			}
	}
	*this = r;
}

template <typename T>
void deleteDuplicateValues(LList<T>& list)
{
	int x;
	list.iterStart();
	elem_link1<T> *p = list.iter();
	while (p != list.getEnd())
	{
		if (p->inf == p->link->inf)
		{
			list.deleteElem(p, x);
		}
		p = list.iter();
	}
}

int main()
{
	LList<int> list;

	list.toEnd(1);
	list.toEnd(1);
	list.toEnd(3);
	list.toEnd(3);
	list.toEnd(5);
	list.toEnd(6);
	list.toEnd(6);
	list.toEnd(9);
	list.toEnd(9);
	list.toEnd(10);
	list.toEnd(10);

	deleteDuplicateValues(list);
	list.print();

	return 0;
}