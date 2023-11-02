#pragma once
#include<iostream>
#include<vector>
#include<random>

using namespace std;

struct Edge
{
	int from;
	int to;
	int weight;

	Edge(int u, int v, int w) : from(u), to(v), weight(w) {}
};

class Graph
{
private:
	int size;
	vector<vector<Edge>> list;


public:
	Graph(int vertices);
	void addEdge(int from, int to, int weight);
	void removeEdge(const Edge& edge);
	void generateRandGraph(int _size, int minWeight, int maxWeight);

	void printGraph();
	void PrimMST();
	void Kruskal();
};