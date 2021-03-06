// DoublynextedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "assert.h"

using namespace std;

template <typename T>
struct elem_link2
{
	T inf;
	elem_link2<T>* prev;
	elem_link2<T>* next;
};

template <typename T>
class DList
{
private:
	elem_link2<T> *start, *end, *currentS, *currentE;
	void deleteList();
	void copyList(DList const &);
public:
	DList();
	~DList();
	DList(DList const &);
	DList& operator= (DList const &);

	void iterStart(elem_link2<T> *p = NULL);
	void iterEnd(elem_link2<T> *p = NULL);

	elem_link2<T>* iterNext();
	elem_link2<T>* iterPrev();

	bool empty() const;
	void toEnd(T const &);//diff
	void insertAfter(elem_link2<T>*, T const &);
	void insertBefore(elem_link2<T>*, T const &);
	bool deleteAfter(elem_link2<T>*, T&);
	bool deleteBefore(elem_link2<T>*, T&);
	void deleteElem(elem_link2<T>*, T&);//diff
	void print() const;//diff
	void print_reverse();//diff
	int lenght() const;//diff
	void concat(const DList&);
	void reverse();
};

template <typename T>
DList<T>::DList()
{
	start = NULL;
	end = NULL;
}

template <typename T>
DList<T>::~DList()
{
	deleteList();
}

template <typename T>
DList<T>::DList(const DList<T>& list)
{
	copeList(list);
}

template <typename T>
DList<T>& DList<T>::operator=(const DList<T>& list)
{
	if (this != &list)
	{
		deleteList();
		copyList(list);
	}
	return *this;
}

template <typename T>
void DList<T>::deleteList()
{
	elem_link2<T> *p;
	while (start)
	{
		p = start;
		start = start->next;
		delete p;
	}
	end = NULL;
}

template <typename T>
void DList<T>::copyList(DList<T> const & list)
{
	start = end = NULL;
	if (list.start)
	{
		elem_link2<T> *p = list.start;
		while (p)
		{
			toEnd(p->inf);
			p = p->next;
		}
	}
}


template <typename T>
void DList<T>::iterStart(elem_link2<T> *p)
{
	if (p) currentS = p;
	else currentS = start;
}

template <typename T>
elem_link2<T>* DList<T>::iterNext()
{
	elem_link2<T> *p = currentS;
	if (currentS) currentS = currentS->next;
	return p;
}

template <typename T>
void DList<T>::iterEnd(elem_link2<T> *p)
{
	if (p) currentE = p;
	else currentE = end;
}

template <typename T>
elem_link2<T>* DList<T>::iterPrev()
{
	elem_link2<T> *p = currentE;
	if (currentE) currentE = currentE->prev;
	return p;
}

template <typename T>
void DList<T>::toEnd(T const & x)
{
	elem_link2<T> *p = end;
	end = new elem_link2<T>;
	end->inf = x;
	end->next = NULL;
	if (p) p->next = end;
	else start = end;
	end->prev = p;
}

template <typename T>
void DList<T>::insertAfter(elem_link2<T> *p, T const & x)
{
	elem_link2<T> *q = new elem_link2<T>;
	assert(q != NULL);
	q->inf = x;
	q->next = p->next;
	if (p == end) end = q;
	p->next = q;
}

template <typename T>
void DList<T>::insertBefore(elem_link2<T> *p, T const & x)
{
	elem_link2<T>* q = new elem_link2<T>;
	assert(q != NULL);
	*q = *p;
	if (p == end) end = q;
	p->inf = x;
	p->next = q;
}

template <typename T>
bool DList<T>::deleteAfter(elem_link2<T>* p, T& x)
{
	if (p->next)
	{
		elem_link2<T> *q = p->next;
		x = q->inf;
		p->next = q->next;
		if (q == end) end = p;
		delete q;
		return 1;
	}
	return 0;
}

template <typename T>
void DList<T>::deleteElem(elem_link2<T>* p, T& x)
{
	x = p->inf;
	if (start == end)
	{
		start = NULL;
		end == NULL;
	}
	else if (p == start)
	{
		start = start->next;
		start->prev = NULL;
	}
	else if (p == end)
	{
		end = p->prev;
		end->next = NULL;
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	delete p;
}

template <typename T>
bool DList<T>::deleteBefore(elem_link2<T>* p, T& x)
{
	if (p != start)
	{
		elem_link2<T> *q = start;
		while (q->next != p) q = q->next;
		deleteElem(q, x);
		return 1;
	}
	return 0;
}


template <typename T>
bool DList<T>::empty() const
{
	return start == NULL;
}

template <typename T>
void DList<T>::print() const
{
	elem_link2<T> *p = start;
	while (p)
	{
		cout << p->inf << " ";
		p = p->next;
	}
	cout << endl;
}

template <typename T>
void DList<T>::print_reverse()
{
	elem_link2<T>* p = end;
	while (p)
	{
		cout << p->inf << " ";
		p = p->prev;
	}
	cout << endl;
}

template <typename T>
int DList<T>::lenght() const
{
	int n = 0;
	elem_link2<T> *p = start;
	while (p)
	{
		n++;
		p = p->next;
	}
	return n;
}

template <typename T>
void DList<T>::concat(const DList<T>& r)
{
	elem_link2<T> *p = r.start;
	while (p)
	{
		toEnd(p->inf);
		p = p->next;
	}
}

template <typename T>
void DList<T>::reverse()
{
	DList<T> r;
	iterStart();
	elem_link2<T> *p = iterNext();
	if (p)
	{
		r.toEnd(p->inf);
		p = p->next;
		while (p)
		{
			r.insertBefore(r.start, p->inf);
			p = p->next;
		}
	}
	*this = r;
}

int main()
{
	/*DList<int> list; 
	int x;
	list.toEnd(1);
	list.toEnd(2);
	list.iterStart();
	elem_link2<int> *p = list.iterNext();
	list.insertBefore(p, 3);
	list.insertAfter(p, 4);
	list.print();
	list.deleteElem(p, x);
	list.print();
	list.iterStart();
	p = list.iterNext();
	list.deleteAfter(p, x);
	list.print();
	list.iterStart();
	p = list.iterNext();
	p = list.iterNext();
	list.deleteBefore(p, x);
	list.print();*/
	return 0;
}