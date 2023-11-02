#include "Graph.h"
#include"2_heap.h"
#include<set>
#include"UnionFind.h"

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
	auto it = list[edge.from].begin();

	while (it != list[edge.from].end())
	{
		if (it->to == edge.to)
		{
			list[edge.from].erase(it);
			break;
		}
		else
		{
			++it;
		}
	}

	it = list[edge.to].begin();

	while (it != list[edge.to].end())
	{
		if (it->to == edge.from)
		{
			list[edge.to].erase(it);
			break;
		}
		else
		{
			++it;
		}
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




void Graph::generateRandGraph(int _size, int minWeigh, int maxWeight)
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