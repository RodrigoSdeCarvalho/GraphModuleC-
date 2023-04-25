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

    for (int i = 0; i < minHeap.size(); i++)
    {
        cout << minHeap.heapNodes[i]->priority << endl;
    }

    for (int i =0; i < numberOfVertices; i++)
    {
        cout << "Node: " << nodes[i]->getName() << endl;
    }

    cout << visitedNodes << endl;
    cout << numberOfVertices << endl;
    while (visitedNodes < numberOfVertices)
    {
        cout << "Visited Nodes: " << visitedNodes << endl;
        shared_ptr<Node> u = minHeap.popMin();
        if ( C[u->getNumber() - 1] == true)
        {
            continue;
        }
        cout << "U: " << u << endl;
        C[u->getNumber() - 1] = true;
            cout << "IF" << endl;
        cout << "U: " << u->getName() << endl;
        visitedNodes++;

        vector<shared_ptr<Connection>> uConnections = u->getConnections();
        for (int i =0; i < uConnections.size(); i++)
        {
            int otherNodeNumber = uConnections[i]->getEndNode()->getNumber();
            cout << "Other Node Number: " << otherNodeNumber << endl;
            if (C[otherNodeNumber - 1] == false)
            {
                //cout<< "u: " << u->getName() << endl;
                shared_ptr<Node> v = uConnections[i]->getEndNode();
                int w = uConnections[i]->getWeight();
                cout << "W: " << w << endl;
                cout << "DV: " << D[v->getNumber() - 1] << endl;
                if (D[v->getNumber() - 1] > D[u->getNumber() - 1] + w) {
                    cout << "DVGET: "<< D[u->getNumber() - 1] << endl;
                    D[v->getNumber() - 1] = D[u->getNumber() - 1] + w;
                    A[v->getNumber() - 1] = u->getNumber() - 1;
                }
            }
        }

    }
    // for (int i = 0; i < numberOfVertices; i++)
    // {
    //     cout << "Heap: " << minHeap.heapNodes[i]->node->getName() << endl;
    // }

    for (int i = 0; i< numberOfVertices; i++)
    {
        cout << "Node: " << i << endl;
        cout << "Ai: " << A[i] << endl;
        cout << "Di: " << D[i] << endl;
        cout << endl;
    }

    // for (int i = 0; i < numberOfVertices; i++) 
    // {
    //     if (i == startNodeIndex) 
    //     {
    //         continue; // Skip the starting node.
    //     }
    //     else
    //     {
    //         cout << "IN ELSE" << endl;
    //         // Print the node number and its path from the starting node.
    //         cout << i << ": ";
    //         shared_ptr<Node> node = nodes[i];
    //         vector<int> path;
    //         while (node->getNumber() != startNodeIndex) 
    //         {
    //             cout << "node: " << node->getNumber() << endl;
    //             cout << "node name: " << node->getName() << endl;
    //             path.push_back(node->getNumber());
    //             int parentPos = A[node->getNumber()];
    //             cout << "parentPos: " << parentPos << endl;
    //             node = nodes[parentPos];
    //             cout << "node: " << node->getName() << endl;
    //         }
    //         path.push_back(startNodeIndex);
    //         reverse(path.begin(), path.end());
    //         for (int j = 0; j < path.size(); j++) {
    //             cout << path[j]+1; // Add 1 to node number to make it 1-indexed.
    //             if (j < path.size()-1) {
    //                 cout << ",";
    //             }
    //         }
    //         // Print the distance from the starting node.
    //         cout << "; d=" << D[i] << endl;
    //     }
    // }
}

void UndirectedGraph::floydWarshall(int startNodeIndex)
{
    // IMPLEMENT FLOYD WARSHALL ALGORITHM.
}

UndirectedGraph::~UndirectedGraph()
{

}