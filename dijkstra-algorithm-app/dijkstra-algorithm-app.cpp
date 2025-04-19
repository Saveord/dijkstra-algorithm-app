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

int main() {
    Graph g;

    Vertex* vertexA = g.AddVertex("A");
    Vertex* vertexB = g.AddVertex("B");
    Vertex* vertexC = g.AddVertex("C");
    Vertex* vertexD = g.AddVertex("D");
    Vertex* vertexE = g.AddVertex("E");
    Vertex* vertexF = g.AddVertex("F");
    Vertex* vertexG = g.AddVertex("G");
    Vertex* vertices[] = { vertexA, vertexB, vertexC, vertexD, vertexE, vertexF, vertexG };

    g.AddUndirectedEdge(vertexA, vertexB, 8);
    g.AddUndirectedEdge(vertexA, vertexD, 3);
    g.AddUndirectedEdge(vertexA, vertexC, 7);
    g.AddUndirectedEdge(vertexB, vertexE, 6);
    g.AddUndirectedEdge(vertexC, vertexD, 1);
    g.AddUndirectedEdge(vertexC, vertexE, 2);
    g.AddUndirectedEdge(vertexD, vertexF, 15);
    g.AddUndirectedEdge(vertexD, vertexG, 12);
    g.AddUndirectedEdge(vertexE, vertexF, 4);
    g.AddUndirectedEdge(vertexF, vertexG, 1);

    // Run Dijkstra's algorithm first.
    unordered_map<Vertex*, PathVertexInfo*> infoMap = DijkstraShortestPath(g, vertexA);

    // Display shortest path for each vertex from vertexA.    
    for (Vertex* vertex : vertices) {
        PathVertexInfo* info = infoMap[vertex];
        if (info->predecessor == nullptr && vertex != vertexA) {
            cout << "A to " << vertex->label << ": no path exists" << endl;
        }
        else {
            cout << "A to " << vertex->label << ": ";
            cout << GetShortestPath(vertexA, vertex, infoMap);
            cout << " (total weight: " << (int)info->distance << ")" << endl;
        }
    }

    // Delete each allocated PathVertexInfo
    for (auto& keyValuePair : infoMap) {
        delete keyValuePair.second;
    }
}