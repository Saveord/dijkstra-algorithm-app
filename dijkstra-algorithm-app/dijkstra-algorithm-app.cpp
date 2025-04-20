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
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<Vertex*, PathVertexInfo*> DijkstraShortestPath(Graph& graph, Vertex* startVertex) {
    // Create the unordered_map for vertex information
    unordered_map<Vertex*, PathVertexInfo*> info;

    // Put all graph vertices in both the info unordered_map and the
    // vector of unvisited vertices
    vector<PathVertexInfo*> unvisited;
    for (Vertex* vertex : graph.GetVertices()) {
        PathVertexInfo* vertexInfo = new PathVertexInfo(vertex);
        unvisited.push_back(vertexInfo);
        info[vertex] = vertexInfo;
    }

    // startVertex has a distance of 0 from itself
    info[startVertex]->distance = 0.0;

    // Iterate through all vertices in the priority queue
    while (unvisited.size() > 0) {
        // Remove info with minimum distance
        PathVertexInfo* currentInfo = PathVertexInfo::RemoveMin(unvisited);

        // Check potential path lengths from the current vertex to all neighbors
        for (Edge* edge : *graph.GetEdgesFrom(currentInfo->vertex)) {
            Vertex* adjacentVertex = edge->toVertex;
            double alternativePathDistance = currentInfo->distance + edge->weight;

            // If a shorter path from startVertex to adjacentVertex is found,
            // update adjacentVertex's distance and predecessor
            PathVertexInfo* adjacentInfo = info[adjacentVertex];
            if (alternativePathDistance < adjacentInfo->distance) {
                adjacentInfo->distance = alternativePathDistance;
                adjacentInfo->predecessor = currentInfo->vertex;
            }
        }
    }

    return info;
}

string GetShortestPath(Vertex* startVertex, Vertex* endVertex,
    unordered_map<Vertex*, PathVertexInfo*> infoMap) {
    // Start from endVertex and build the path in reverse.
    string path = "";
    Vertex* currentVertex = endVertex;
    while (currentVertex != startVertex) {
        path = " -> " + currentVertex->label + path;
        currentVertex = infoMap[currentVertex]->predecessor;
    }
    path = startVertex->label + path;
    return path;
}

//matrix code 
void addEdge(vector<vector<int>>& mat, int i, int j)
{
    mat[i][j] = 1;
    mat[j][i] = 1; // Since the graph is undirected
}

void displayMatrix(vector<vector<int>>& mat)
{
    int V = mat.size();
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

int main()
{

    // Create a graph with 4 vertices and no edges
    // Note that all values are initialized as 0
    int V = 4;
    vector<vector<int>> mat(V, vector<int>(V, 0));

    // Now add edges one by one
    addEdge(mat, 0, 1);
    addEdge(mat, 0, 2);
    addEdge(mat, 1, 2);
    addEdge(mat, 2, 3);

    cout << "Adjacency Matrix Representation" << endl;
    displayMatrix(mat);
    Vertex v = Vertex("A");
    v.id = 1;
    cout << v.label << "id = " << v.id << endl;

    Graph g = Graph();
    g.adjacentMatrix = mat;
    displayMatrix(g.adjacentMatrix);

    return 0;
}
