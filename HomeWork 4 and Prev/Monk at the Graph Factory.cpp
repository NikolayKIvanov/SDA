
#include "iostream"
#include "queue"
#include "fstream"

using namespace std;

template <typename T>
struct elem_link1
{
	T inf;
	elem_link1<T>* link;
};

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
LList<T> BFS(const T a, graph<T>& g)
{
	LList<T> l;
	queue<T> q; q.push(a);
	l.toEnd(a);
	while (!q.empty())
	{
		T x; x = q.front();
		q.pop();
		elem_link1<T>* p = g.point(x);
		p = p->link;
		while (p)
		{
			if (!member(p->inf, l))
			{
				q.push(p->inf);
				l.toEnd(p->inf);
			}
			p = p->link;
		}
	}
	return l;
}

template <typename T>
bool member(const T& a, LList<T> l)
{
	l.iterStart();
	elem_link1<T>* p = l.iter();
	while (p && p->inf != a) p = p->link;
	return p != NULL;
}

template <typename T>
void Cycles(const T a, graph<T>& g, LList<T>& l, LList<T>& temp)
{
	l.toEnd(a);
	elem_link1<T>* p = g.point(a);
	p = p->link;
	while (p)
	{
		if (!member(p->inf, l)) Cycles(p->inf, g, l, temp);
		else
		{
			temp.toEnd(p->inf);
		}
		p = p->link;
	}
}

template <typename T>
bool noCycles(const T root, graph<T>& g, LList<T>& l, LList<T>& temp)
{
	Cycles(root, g, l, temp);
	temp.iterStart();
	elem_link1<int> *p = temp.iter();
	while (p)
	{
		if (member(p->inf, l))
		{
			return false;
		}
		p = p->link;
	}
	return true;
}

template <typename T>
void GraphFromFile(graph<T>& g, ifstream& text)
{
	text.open("test.txt");
	int n, m;
	LList<T> l;
	while (!text.eof())
	{
		text >> n;
		text >> m;
		if (!member(n, l))
		{
			l.toEnd(n);
			g.addTop(n);
		}
		g.addRib(n, m);
		if (!member(m, l))
		{
			l.toEnd(m);
			g.addTop(m);
		}
	}
	text.close();
}

template <typename T>
T getRoot(T& root, ifstream& text)
{
	text.open("test.txt");
	text >> root;
	text.close();
	return root;
}
int main()
{
	graph<int> g;
	ifstream text;
	GraphFromFile(g, text);
	int root = getRoot(root, text);
	LList<int> visited, again;
	if (noCycles(root, g, visited, again) && BFS(root, g).lenght() == g.vertexes().lenght())
	{
		cout << "Is tree!" << endl;
	}
	else cout << "Is not tree!" << endl;
	return 0;
}

