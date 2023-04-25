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

void UndirectedGraph::addEdge(shared_ptr<Node> node1, shared_ptr<Node> node2, int weight)
{
    weak_ptr<Node> node1WeakPtr(node1);
    weak_ptr<Node> node2WeakPtr(node2);

    shared_ptr<Connection> connection1SharedPtr = make_shared<Connection>(weight, node1WeakPtr, node2WeakPtr, true);
    shared_ptr<Connection> connection2SharedPtr = make_shared<Connection>(weight, node2WeakPtr, node1WeakPtr, true);
    
    this->edges.push_back(connection1SharedPtr);
    this->edges.push_back(connection2SharedPtr);

    weak_ptr<Connection> connection1WeakPtr(connection1SharedPtr);
    node1->addConnection(connection1SharedPtr);

    weak_ptr<Connection> connection2WeakPtr(connection2SharedPtr);
    node2->addConnection(connection2SharedPtr);

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
        D[i] = 1000000; // Initialize with infinity.
        A[i] = -1; // Initialize with -1.
    }

    D[startNodeIndex] = 0; // Set the distance from the start node to itself to 0.
    
    A[startNodeIndex] = -1; // Set the parent of the start node to -1.

    MinHeap minHeap = MinHeap(); // Create a min heap. 
    for (int n = 0; n < numberOfVertices; n++)
    {
        minHeap.insert(this->nodes[n], D[n]);
    }

    while (visitedNodes < numberOfVertices)
    {
        shared_ptr<Node> u = minHeap.popMin();
        C[u->getNumber() - 1] = true;
        visitedNodes++;
        vector<shared_ptr<Connection>> uConnections = u->getConnections();
        for (int i =0; i < uConnections.size(); i++)
        {
            int otherNodeNumber = uConnections[i]->getEndNode()->getNumber();
            if (C[otherNodeNumber - 1] == false)
            {
                shared_ptr<Node> v = uConnections[i]->getEndNode();
                int w = uConnections[i]->getWeight();
                if (D[v->getNumber() - 1] > D[u->getNumber() - 1] + w) 
                {
                    D[v->getNumber() - 1] = D[u->getNumber() - 1] + w;
                    A[v->getNumber() - 1] = u->getNumber() - 1;
                    minHeap.updatePriority(v, D[v->getNumber() - 1]);
                }
            }
        }

    }

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (i != startNodeIndex)
        {
            vector<int> path;
            int currentNodeIndex = i;
            while (currentNodeIndex != startNodeIndex)
            {
                path.insert(path.begin(), currentNodeIndex + 1);
                currentNodeIndex = A[currentNodeIndex];
            }
            path.insert(path.begin(), startNodeIndex + 1);

            cout << path[0] << ": ";
            for (int j = 1; j < path.size() - 1; j++)
            {
                cout << path[j] << ",";
            }
            cout << path[path.size() - 1] << "; d = " << D[i] << endl;
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
