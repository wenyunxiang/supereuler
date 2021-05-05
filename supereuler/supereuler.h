#pragma once

#include<iostream>
#include<string>
#include<cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

class Graph_DG {
public:
	int vexnum;				//The number of vertices in the graph
	int edge;				//Number of edges of the graph
	int **arc;				//Adjacency matrix
	int ** dis;				//Record the length of the shortest path for each vertex
	int ** path;			//Record the sequence of each shortest path
	int degree[100];		//Record the degree of vertices
	int pre;				//Record the first vertex or pubilc point of a pubilc edge found
	int beh;				//Record the second vertex of a pubilc edge
	int style;				//Whether the starting point value is inserted at the end is determined by the pubilc edge or the pubilc point

	Graph_DG(int vexnum);								//The constructor function

	~Graph_DG();										//The destructor function

	void clean();										//The dynamic array "sequence" reset to zero

	void Floyd();										//Find shortest path

	bool print_path();									//Merge vertex sequences and print them

	bool check();										//Check that all vertices are included

	bool public_side();									//Find and set public edges

	bool public_point();								//Find and set pubilc points
};