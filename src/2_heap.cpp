#include "2_heap.h"

int BinaryHeap::lefchild(int l)
{
	return l * 2 + 1;
}

int BinaryHeap::rightchild(int r)
{
	return r * 2 + 2;
}

int BinaryHeap::parent(int p)
{
	if (p > 0)
	{
		return (p - 1) / 2;
	}
	else
	{
		throw std::invalid_argument("invalid argument!");
	}
}

void BinaryHeap::elem_up(int index)
{
	while (index > 0)
	{
		if (heap[index].second < heap[parent(index)].second)
		{
			swap(heap[index], heap[parent(index)]);
			index = parent(index);
		}
		else
		{break;}
	}
}

void BinaryHeap::elem_down(int index)
{
	

		int left = lefchild(index);
		int right = rightchild(index);

		int small = index;
		if (left < heapSize() && heap[left].second < heap[small].second)
		{

			small = left;
		}
		if (right < heapSize() && heap[right].second < heap[small].second)
		{
			small = right;
		}

		if (small != index)
		{
			swap(heap[index], heap[small]);
			elem_down(small);
		}
}

int BinaryHeap::heapSize()
{
	return heap.size();
}

bool BinaryHeap::isHempty()
{
	return heapSize() == 0;
}

void BinaryHeap::addElem(int vertex, int weight)
{
	heap.push_back({vertex, weight});
	
	int i = heapSize() - 1;

	elem_up(i);
}

void BinaryHeap::pop()
{
	if (!isHempty())
	{
		heap[0] = heap.back();
		heap.pop_back();
		elem_down(0);
	}
	else
	{
		throw "The heap is empty.";
	}
}

pair<int, int> BinaryHeap::top()
{
	if (!isHempty())
	{
		return heap.at(0);
	}
}
