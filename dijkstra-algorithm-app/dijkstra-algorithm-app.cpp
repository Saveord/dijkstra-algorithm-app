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

void displayMatrix(Graph& graph) {
    const auto& vertices = graph.GetVertices();
    size_t size = vertices.size();

    // Create a mapping of vertices to indices
    unordered_map<Vertex*, int> vertexIndexMap;
    for (size_t i = 0; i < size; ++i) {
        vertexIndexMap[vertices[i]] = i;
    }

    // Initialize the adjacency matrix
    vector<vector<double>> matrix(size, vector<double>(size, numeric_limits<double>::infinity()));

    // Fill the adjacency matrix with edge weights
    for (Edge* edge : graph.GetEdges()) {
        int fromIndex = vertexIndexMap[edge->fromVertex];
        int toIndex = vertexIndexMap[edge->toVertex];
        matrix[fromIndex][toIndex] = edge->weight;
    }

    // Print the adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (matrix[i][j] == numeric_limits<double>::infinity()) {
                cout << "INF ";
            }
            else {
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}


int main() {
    Graph g;

    Vertex* vertexA = g.AddVertex("A");
    Vertex* vertexB = g.AddVertex("B");
    Vertex* vertexC = g.AddVertex("C");
    Vertex* vertexD = g.AddVertex("D");
    Vertex* vertices[] = { vertexA, vertexB, vertexC, vertexD };

    g.AddUndirectedEdge(vertexA, vertexB, 8);
    g.AddUndirectedEdge(vertexA, vertexD, 3);
    g.AddUndirectedEdge(vertexA, vertexC, 7);
    g.AddUndirectedEdge(vertexC, vertexD, 1);;

    displayMatrix(g);
}