/*
Alexa Wu

Lab: Priority Queue

4/5/2025

Windows 11 Home, 24H2, ISO C++14 Standard

Description: This application uses Dijkstra's algorithm to find the shortest path using an adjacient matrix.
*/

#include <iostream>
#include "Graph.h"
#include "PathVertexInfo.h"
using namespace std;

int main()
{
	Graph g = Graph(5);
	g.addWeightedEdge(0, 1, 5);
	g.addWeightedEdge(0, 2, 44);
	g.addWeightedEdge(0, 3, 2);
	g.addWeightedEdge(0, 4, 1);
	g.addWeightedEdge(1, 2, 26);
	g.addWeightedEdge(1, 3, 14);
	g.addWeightedEdge(1, 4, 7);
	g.addWeightedEdge(2, 3, 9);
	g.addWeightedEdge(2, 4, 3);
	g.addWeightedEdge(3, 4, 68);

	g.printAdjacencyMatrix();
	cout << endl;
	DijkstraShortestPath(g.adjacencyMatrix, 0);
}
