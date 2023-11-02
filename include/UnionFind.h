#pragma once
#include<vector>

using namespace std;

class UnionFind
{
public:

	vector<int> parent, rank;

	UnionFind(int n)
	{
		parent.resize(n);
		rank.resize(n, 0);

		for (int i = 0; i < n; ++i)
		{
			parent[i] = i;
			rank[i] = 0;
		}
	}

	int find_root(int u) // find the root of the set
	{
		if (u == parent[u]) return u;

		return parent[u] = find_root(parent[u]);
	}


	bool union_sets(int u, int v) // union of two sets
	{
		u = find_root(u);
		v = find_root(v);
	
		if (u == v)
			return false;
	
		if (rank[u] < rank[v])
			swap(u, v);
	
		if (rank[u] == rank[v])
			rank[u]++;
	
		parent[v] = u;

		return true;
	}
};
