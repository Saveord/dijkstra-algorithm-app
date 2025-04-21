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
		adjacencyMatrix = vector<vector<int>> (n, vector<int>(n, INT_MAX));
		for (int u = 0; u < adjacencyMatrix.size(); u++)
		{
			for (int v = 0; v < adjacencyMatrix.size(); v++)
			{
				if (u == v)
				{
					adjacencyMatrix[u][v] = 0;
					adjacencyMatrix[v][u] = 0;
				}
			}
		}
	}

	void addWeightedEdge(int u, int v, int weight)
	{
		if (u == v)
		{
			cout << "Cannot add edge to itself" << endl;
		}
		else
		{
			adjacencyMatrix[u][v] = weight;
			adjacencyMatrix[v][u] = weight;
		}
	}

	void printAdjacencyMatrix()
	{
		cout << "Adjacency Matrix for the Graph: " << endl;
		int n = adjacencyMatrix.size();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (adjacencyMatrix[i][j] == INT_MAX)
				{
					cout << "INF" << " ";
				}
				else
				{
					cout << adjacencyMatrix[i][j] << " ";
				}
			}
			cout << endl;
		}
	}
};
#endif