// MergeSortedLists.cpp : Defines the entry point for the console application.
//
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
LList<T> mergeLists(LList<T> List1, LList<T> List2)
{
	LList<T> MergedL;
	List1.iterStart();
	List2.iterStart();
	elem_link1<T> *p = List1.iter();
	elem_link1<T> *q = List2.iter();
	while (p != NULL && q != NULL)
	{
		if (p->inf < q->inf)
		{
			MergedL.toEnd(p->inf);
			p = List1.iter();
		}
		else
		{
			MergedL.toEnd(q->inf);
			q = List2.iter();
		}
	}
	if (p)
	{
		while (p != NULL)
		{
			MergedL.toEnd(p->inf);
			p = List1.iter();
		}
	}
	else
	{
		while (q != NULL)
		{
			MergedL.toEnd(q->inf);
			q = List2.iter();
		}
	}
	return MergedL;
}
int main()
{
	LList<int> list1, list2;

	list1.toEnd(1);
	list1.toEnd(3);
	list1.toEnd(5);
	list1.toEnd(7);
	list1.toEnd(9);
	list2.toEnd(2);
	list2.toEnd(4);
	list2.toEnd(6);
	list2.toEnd(8);
	list2.toEnd(10);
	list2.toEnd(11);

	mergeLists(list1, list2).print();
	return 0;
}


