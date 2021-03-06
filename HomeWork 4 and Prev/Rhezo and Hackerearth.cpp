
#include "iostream"
#include "graph.cpp"

template <typename T>
struct elem_link1
{
	T inf;
	elem_link1<T>* link;
};

struct pairs
{
	int node1;
	int node2;
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
void createGraph(graph<T>& g, int& N, int M, pairs track[20])
{
	LList<T> l;
	int x, y, i = 0;
	while (M != 0)
	{
		cin >> x >> y;
		track[i].node1 = x;
		track[i].node2 = y;
		i++;
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
void check(graph<T>& g, pairs& X)
{	
	g.deleteRib(X.node1, X.node2);
	g.deleteRib(X.node2, X.node1);
	LList<T> l1 = g.vertexes();
	l1.iterStart();
	elem_link1<T>* p = l1.iter();
	LList<T> l = BFS(p->inf, g);
	if (l.lenght() == l1.lenght()) cout << "Happy" << endl;
	else cout << "Unappy" << endl;
	g.addRib(X.node1, X.node2);
	g.addRib(X.node2, X.node1);
}
int main()
{
	graph<int> g;
	int N, M;
	cin >> N >> M;
	pairs* track = new pairs[M];
	createGraph(g, N, M, track);
	int Q, X;
	cin >> Q;
	while (Q != 0)
	{
		cin >> X;
		check(g, track[X-1]);
		Q--;
	}
	delete[] track;
	return 0;
}