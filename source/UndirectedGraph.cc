#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <algorithm>
#include <memory>

#include "UndirectedGraph.h"
#include "AbstractGraph.h"
#include "Node.h"
#include "Connection.h"
#include "MinHeap.h"
#include "HeapNode.h"

using namespace std;
using namespace GraphModule;

UndirectedGraph::UndirectedGraph()
{
    this->numberOfEdges = 0;
}

int UndirectedGraph::getDegreeOfNode(int nodeKey)
{
    shared_ptr<Node> node = this->nodes[nodeKey];
    return (node->getConnections()).size();
}

void UndirectedGraph::addEdge(shared_ptr<Node> startNode, shared_ptr<Node> endNode, int weight)
{
    weak_ptr<Node> startNodeWeakPtr(startNode);
    weak_ptr<Node> endNodeWeakPtr(endNode);

    shared_ptr<Connection> connectionSharedPtr = make_shared<Connection>(weight, startNodeWeakPtr, endNodeWeakPtr, true);
    this->edges.push_back(connectionSharedPtr);

    weak_ptr<Connection> connectionWeakPtr(connectionSharedPtr);
    startNode->addConnection(connectionWeakPtr);
    endNode->addConnection(connectionWeakPtr);

    this->numberOfEdges++;
}

void UndirectedGraph::BFS(int startNodeIndex)
{
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<shared_ptr<Node>> nodes = this->nodes;
    bool V[numberOfVertices]; // Array of visited nodes.
    int D[numberOfVertices]; // Array of distances from the start node.
    int A[numberOfVertices]; // Array of parent nodes.
    vector<vector<int>> levels; // Vector of vectors to store vertices found at each level
    for (int i = 0; i <= numberOfVertices; i++)
    {
        V[i] = false; // Initialize with false.
        D[i] = numeric_limits<int>::max(); // Initialize with infinity.
        A[i] = -1; // Initialize with -1.
    }
    V[startNodeIndex] = true; // Mark the start node as visited.
    D[startNodeIndex] = 0; // Set the distance from the start node to itself to 0.
    A[startNodeIndex] = -1; // Set the parent of the start node to -1.

    queue<int> Q; // Create a queue.
    Q.push(startNodeIndex); // Push the start node to the queue.
    levels.push_back(vector<int>({startNodeIndex})); // Add the start node to level 0
    while (!Q.empty())
    {
        int u = Q.front(); // Get the first element in the queue.
        Q.pop(); // Remove the first element in the queue.
        vector<shared_ptr<Connection>> connections = nodes[u]->getConnections(); // Get the connections of the start node.

        for (int i = 0; i != connections.size(); ++i)
        {
            shared_ptr<Connection> conn = connections[i];
            shared_ptr<Node> vNode = (conn)->getEndNode(); // Get the end node of the connection.
            int v = vNode->getNumber() - 1; // Get the index of the end node of the connection.
            if (!V[v])
            { // If the end node of the connection is not visited.
                V[v] = true; // Mark the end node as visited.
                D[v] = D[u] + 1; // Set the distance from the start node to the end node to the distance from the start node to the start node of the connection plus 1.
                A[v] = u; // Set the parent of the end node to the start node of the connection.
                Q.push(v); // Push the end node to the queue.
            }
        }
    }

    // Print the levels and vertices found in each level.
    for (int level = 0; level <= numberOfVertices; level++) {
        bool foundVertices = false;
        for (int i = 0; i < numberOfVertices; i++) {
            if (D[i] == level) {
                if (!foundVertices) {
                    cout << level << ":";
                    foundVertices = true;
                }
                cout << " " << nodes[i]->getName();
            }
        }
        if (!foundVertices) {
            break; // No more vertices to print.
        }
        cout << endl;
    }
}

void UndirectedGraph::eulerianCycle(int startNodeIndex)
{
    // IMPLEMENT EULERIAN CYCLE ALGORITHM.
}

void UndirectedGraph::dijkstra(int startNodeIndex)
{
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<shared_ptr<Node>> nodes = this->nodes; // Vector of nodes in the graph.
    int D[numberOfVertices]; // Array of distance
    int A[numberOfVertices]; // Array of parent nodes.
    vector<bool> C(numberOfVertices, false); // Vector of visited nodes.
    int visitedNodes = 0; // Counter for the number of visited nodes.

    for (int i = 0; i < numberOfVertices; i++)
    {
        D[i] = numeric_limits<int>::max(); // Initialize with infinity.
        A[i] = -1; // Initialize with -1.
    }

    D[startNodeIndex] = 0; // Set the distance from the start node to itself to 0.
    A[startNodeIndex] = -1; // Set the parent of the start node to -1.

    vector<shared_ptr<HeapNode>> heapNodes = vector<shared_ptr<HeapNode>>(numberOfVertices);    
    for (int n = 0; n < numberOfVertices; n++)
    {
        heapNodes[n] = make_shared<HeapNode>(n, nodes[n], D[n]);
    }
    MinHeap minHeap = MinHeap(heapNodes); // Create a min heap.

    while (visitedNodes < numberOfVertices)
    {
        shared_ptr<Node> u = minHeap.popMin();
        C[u->getNumber()] = true;
        visitedNodes++;

        for (vector<shared_ptr<Connection>>::iterator it = u->getConnections().begin(); it != u->getConnections().end(); ++it)
        {
            shared_ptr<Node> v = (*it)->getEndNode();
            int w = (*it)->getWeight();

            if (D[v->getNumber()] > D[u->getNumber()] + w) {
                D[v->getNumber()] = D[u->getNumber()] + w;
                A[v->getNumber()] = u->getNumber();
            }
        }
    }
}

void UndirectedGraph::floydWarshall(int startNodeIndex)
{
    // IMPLEMENT FLOYD WARSHALL ALGORITHM.
}

UndirectedGraph::~UndirectedGraph()
{

}