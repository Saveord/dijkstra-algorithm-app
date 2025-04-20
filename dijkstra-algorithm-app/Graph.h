#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Graph
{

public:
	
	vector<vector<int>> adjacencyMatrix;

	Graph(int n)
	{
		adjacencyMatrix = vector<vector<int>> (n, vector<int>(n, 0));
	}

	void addEdge(int u, int v)
	{
		adjacencyMatrix[u][v] = 1;
		adjacencyMatrix[v][u] = 1;
	}

	void printAdjacencyMatrix()
	{
		cout << "Adjacency Matrix for the Graph: " << endl;
		int n = adjacencyMatrix.size();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << adjacencyMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};
#endif