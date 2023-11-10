#include "Graph.h"
#include"2_heap.h"
#include<set>
#include"UnionFind.h"
#include <queue>

Graph::Graph(int vertices) : size(vertices)
{
	list.resize(size);
}

void Graph::addEdge(int from, int to, int weight)
{
	Edge edge = { from, to, weight };

	list[from].push_back(edge);

	edge = { to, from, weight };

	list[to].push_back(edge);
}

void Graph::removeEdge(const Edge& edge)
{
	// Создаем список индексов элементов для удаления
	std::vector<int> indicesToRemove;

	// Поиск индексов ребра в списке смежности вершины "from"
	for (int i = 0; i < list[edge.from].size(); ++i)
	{
		if (list[edge.from][i].to == edge.to)
		{
			indicesToRemove.push_back(i);
		}
	}

	// Удаляем найденные элементы из списка смежности вершины "from"
	for (int index : indicesToRemove)
	{
		list[edge.from].erase(list[edge.from].begin() + index);
	}

	// Очищаем список для следующей операции
	indicesToRemove.clear();

	// Поиск индексов ребра в списке смежности вершины "to"
	for (int i = 0; i < list[edge.to].size(); ++i)
	{
		if (list[edge.to][i].to == edge.from)
		{
			indicesToRemove.push_back(i);
		}
	}

	// Удаляем найденные элементы из списка смежности вершины "to"
	for (int index : indicesToRemove)
	{
		list[edge.to].erase(list[edge.to].begin() + index);
	}
}

void Graph::printGraph()
{
	for (size_t vert = 0; vert < size; ++vert)
	{
		for (const Edge& edge : list[vert])
		{
			std::cout << "(" << edge.from << " - " << edge.to << ") Weight: " << edge.weight << endl;
		}
		std::cout << endl;
	}
}

// Prima

void Graph::PrimMST()
{
	BinaryHeap minHeap;

	vector<bool> visit(size, false);
	vector<int> key(size, INT_MAX); //weigth
	vector<int> parent(size, -1); 
	
	int src = 0;
	key[src] = 0;


	minHeap.addElem(src, 0);

	while (!minHeap.isHempty())
	{
		int u = minHeap.top().first;
		minHeap.pop();

		if (visit[u]) continue; // Пропустить уже посещенные вершины
		visit[u] = true;

		for (const auto& pair : list[u])
		{
			int v = pair.to;
			int weight = pair.weight;

			if (!visit[v] && weight < key[v])
			{
				key[v] = weight;
				parent[v] = u;
				minHeap.addElem(v, key[v]);
			}
		}
	}
	int count = 0;
	int minw = 0;
	for (int i = 1; i < size; i++) {
		minw += key[i];
		count++;
		//std::cout << "Edge: " << parent[i] << " - " << i << " weight: " << key[i] << std::endl;
	}
	std::cout << minw << std::endl;
	std::cout << "total edges: " << count << endl;
	std::cout << "Prim is done" << std::endl;
}


// Kruskal

void Graph::Kruskal()
{
	vector<Edge> edges;

	for (const auto& edg : list)
	{
		edges.insert(edges.end(), edg.begin(), edg.end());
	}

	sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {return a.weight < b.weight; });
	
	vector<Edge> mst;

	UnionFind uf(size);

	for (const Edge& edge : edges)
	{
		if (uf.union_sets(edge.from, edge.to))
		{
			mst.push_back(edge);
		}
	}
	int min_weight = 0;
	int count = 0;
	for (const Edge& edge : mst)
	{
		min_weight += edge.weight;
		//std::cout << "Edge: " << edge.from << " - " << edge.to << " Weight: " << edge.weight << std::endl;
	}
	std :: cout << endl;
	std ::cout << min_weight << endl;
	std::cout << "total edges: " << mst.size() << endl;

	cout << "kruskal is and" << endl;
}

bool Graph::BFS()
{
	if (size == 0)
		return false;

	vector<bool> visited(size, false);
	queue<int> q;
	int start_v = 0;

	q.push(start_v);
	visited[start_v] = true;

	while (!q.empty())
	{
		int c_vert = q.front();
		q.pop();

		for (const Edge& edge : list[c_vert])
		{
			if (!visited[edge.to])
			{
				visited[edge.to] = true;
				q.push(edge.to);
			}
		}
	}
	for (bool v : visited)
	{
		if (!v)
		{
			return false;
		}
	}
	return true;
}





void Graph::generateRandGraph(int _size, int numEdge, int minWeigh, int maxWeight)
{
	if (minWeigh < 1) throw "minWeight should be greater than or equal to 1";

	size = _size;
	list.clear();
	list.resize(size);

	mt19937 rng(time(0));

	uniform_int_distribution<int> weightDist(1, maxWeight);
	uniform_int_distribution<int> vertDist(0, size-1);

	if (size - 1 < numEdge && numEdge <= (((size) * (size - 1)) / 2))
	{
		for (int from = 0; from < size - 1; ++from)
		{
			for (int to = 0; to < 1; ++to)
			{
				int weight = weightDist(rng);
				addEdge(from, from + 1, weight);
			}
		}

		addEdge(size - 1, 0, weightDist(rng));


		int count = 0;
		while (count != (numEdge - size))
		{
			int weight = weightDist(rng);

			int v = vertDist(rng);
			int u = vertDist(rng);
			bool ver = false;

			if (u != v)
			{
				for (const Edge& edge : list[v])
				{
					if (edge.to == u)
					{
						ver = true;
					}
				}

				if (!ver) {
					addEdge(v, u, weight);
					++count;
				}
			}


		}
	}
	else
	{
		throw "error Edges!";
	}
}

void Graph::generateRandFullGraph(int _size, int minWeigh, int maxWeight)
{
	if (minWeigh < 1) throw "minWeight should be greater than or equal to 1";

	size = _size;
	list.clear();
	list.resize(size);

	mt19937 rng(time(0));

	uniform_int_distribution<int> weightDist(1, maxWeight);

	for (int from = 0; from < size; ++from)
	{
		for (int to = from + 1; to < size; ++to)
		{
			int weight = weightDist(rng);
			addEdge(from, to, weight);
		}
	}
}