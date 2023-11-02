#include<iostream>
#include "2_heap.h"
#include"Graph.h"
#include"Timer.h"


using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	Graph a(6);



	a.generateRandGraph(100, 1, 100);
	
	a.PrimMST();
	
	a.Kruskal();


	return 0;
} 
