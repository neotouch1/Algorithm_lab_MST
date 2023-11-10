#include<iostream>
#include "2_heap.h"
#include"Graph.h"
#include"Timer.h"
#include<fstream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	Graph a(6);

	ofstream f;
	f.open("time.txt");

	Timer t1;
	Timer t2;

	int vert = 10000;
	int edge = 10000000;
	int minV = 1;
	int maxV = 1;

	if (f.is_open()) {

		for (maxV; maxV < 200; ++maxV) {

			a.generateRandFullGraph(vert, minV, maxV);

			t1.reset();
			a.PrimMST();
			double time1 = t1.elapsed();
			cout << time1 << endl;

			t2.reset();
			a.Kruskal();
			double time2 = t2.elapsed();
			cout << time2 << endl;
			cout << endl;

			f << time1 << " " << time2 << endl;
		}
	}
	 
	//a.generateRandGraph(vert, edge, minV, maxV);

	//
	//a.printGraph();
	//a.Kruskal();

	//a.PrimMST();


	return 0;
} 
