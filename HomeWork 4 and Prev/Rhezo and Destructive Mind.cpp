
#include "iostream"
#include "graph.cpp"

template <typename T>
struct elem_link1
{
	T inf;
	elem_link1<T>* link;
};

template <typename T>
bool member(const T& a, LList<T> l)
{
	l.iterStart();
	elem_link1<T>* p = l.iter();
	while (p && p->inf != a) p = p->link;
	return p != NULL;
}

template <typename T>
void createGraph(graph<T>& g, int& N, int M)
{
	LList<T> l;
	int x, y;
	while (M != 0)
	{
		cin >> x >> y;
		if (!member(x, l))
		{
			l.toEnd(x);
			g.addTop(x);
		}
		if (!member(y, l))
		{
			l.toEnd(y);
			g.addTop(y);
		}
		g.addRib(x, y);
		g.addRib(y, x);
		M--;
	}
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
void check(graph<T> g, int& X)
{
	elem_link1<T>* q = g.point(X);
	q = q->link;
	int counter = 0;
	while (q)
	{
		counter++;
		q = q->link;
	}
	g.deleteTop(X);
	LList<T> l1 = g.vertexes();
	l1.iterStart();
	elem_link1<T>* p = l1.iter();
	LList<T> l = BFS(p->inf, g);
	if (l.lenght() == l1.lenght()) cout << "Not Satisfied" << endl;
	else cout << "Satisfied " << counter << endl;
}
int main()
{
	graph<int> g;
	int N, M;
	cin >> N >> M;
	createGraph(g, N, M);
	int Q, X;
	cin >> Q;
	while (Q != 0)
	{
		cin >> X;
		check(g, X);
		Q--;
	}
	return 0;
}



