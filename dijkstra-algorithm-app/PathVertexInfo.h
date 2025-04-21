#ifndef PATHVERTEXINFO_H
#define PATHVERTEXINFO_H
#include <limits>
#include <vector>
using namespace std;

inline int GetShortestPath(vector<int>& dist, const vector<bool>& visited, int vertices)
{
	int min = INT_MAX;
	int minIndex = -1;

	for (int v = 0; v < vertices; v++) {
		if (!visited[v] && dist[v] <= min) {
			min = dist[v];
			minIndex = v;
		}
	}
	return minIndex;
}

inline void DijkstraShortestPath(vector<vector<int>>& graph, int src) {
	int vertices = graph.size();
	vector<int> dist(vertices, INT_MAX); // Distance from source to each vertex
	vector<bool> visited(vertices, false); // Visited vertices
	dist[src] = 0; // Distance to source is 0
	for (int count = 0; count < vertices - 1; count++) {
		int u = GetShortestPath(dist, visited, vertices);
		visited[u] = true;
		for (int v = 0; v < vertices; v++) {
			if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] +
				graph[u][v] < dist[v]) {
				dist[v] = dist[u] + graph[u][v];
			}
		}
	}
	// Print the shortest distances
	cout << "Vertex\tShortest Distance From Vertex " << src << endl;
	for (int i = 0; i < vertices; i++) {
		cout << i << "\t" << dist[i] << endl;
	}
}
#endif

