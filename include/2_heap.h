#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include"2_heap.h"
#include"Graph.h"

using namespace std;


class BinaryHeap
{
private:

	vector<pair<int, int>> heap;

	int lefchild(int l);  // returns the left child element

	int rightchild(int r); // returns the right child element

	int parent(int p);    // returns the parent

	void elem_up(int index);	// pushes the element up
	
	void elem_down(int index);  // pushes the element down

public:
	int heapSize();

	bool isHempty();

	void addElem(int vertex, int weight);

	void pop();

	pair<int, int> top();


};