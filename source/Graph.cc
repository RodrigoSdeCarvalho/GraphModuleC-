#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <algorithm>

#include "Graph.h"
#include "Node.h"
#include "Connection.h"
#include "MinHeap.h"

using namespace std;
using namespace GraphModule;

Graph::Graph(string inputFilePath)
{
    this->numberOfVertices = 0;
    this->numberOfEdges = 0;
    this->numberOfArcs = 0;

    this->buildGraphFromInputFile(inputFilePath);
}

void Graph::buildGraphFromInputFile(string inputFilePath) //TEST THIS PROPERLY.
{
    char* inputFilePathChar = &inputFilePath[0];

    ifstream inputFile;

    inputFile.open(inputFilePathChar, ios::in);

    bool inputVertices = false;
    bool inputEdges = false;
    bool inputArcs = false;

    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (ss >> token)
            {
                tokens.push_back(token);
            }

            if (tokens[0] == "*vertices")
            {
                inputVertices = true;
                continue;
            }

            if (tokens[0] == "*edges")
            {
                inputVertices = false;
                inputEdges = true;
                continue;
            }

            if (tokens[0] == "*arcs")
            {
                inputVertices = false;
                inputArcs = true;
                continue;
            }

            if (inputVertices)
            {
                Node* node = new Node(stoi(tokens[0]), tokens[1]);
                this->addNode(node);
            }

            if (inputEdges)
            {
                Node* startNode = this->nodes[stoi(tokens[0]) - 1];
                Node* endNode = this->nodes[stoi(tokens[1]) - 1];
                int weight = stoi(tokens[2]);

                this->addEdge(startNode, endNode, weight);
            }

            if (inputArcs)
            {
                Node* startNode = this->nodes[stoi(tokens[0]) - 1];
                Node* endNode = this->nodes[stoi(tokens[1]) - 1];
                int weight = stoi(tokens[2]);

                this->addArc(startNode, endNode, weight);
            }
        }
    }
}

void Graph::BFS(int startNodeIndex)
{
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<Node*> nodes = this->nodes; // Vector of nodes in the graph.
    bool *V = new bool[numberOfVertices]; // Array of visited nodes.
    int D[numberOfVertices]; // Array of distances from the start node.
    int *A = new int[numberOfVertices]; // Array of parent nodes.

    for (int i = 0; i <= numberOfVertices; i++) {
        V[i] = false; // Initialize with false.
        D[i] = numeric_limits<int>::max(); // Initialize with infinity.
        A[i] = -1; // Initialize with -1.
    }

    V[startNodeIndex] = true; // Mark the start node as visited.
    D[startNodeIndex] = 0; // Set the distance from the start node to itself to 0.
    A[startNodeIndex] = -1; // Set the parent of the start node to -1.

    queue<int> Q; // Create a queue.
    Q.push(startNodeIndex); // Push the start node to the queue.

    while (!Q.empty())
    {
        int u = Q.front(); // Get the first element in the queue.
        Q.pop(); // Remove the first element in the queue.

        for (vector<Connection*>::iterator it = nodes[u]->getConnections().begin(); it != nodes[u]->getConnections().end(); ++it)
        {
            int v = (*it)->getEndNode()->getNumber(); // Get the end node of the connection.
            if (!V[v]) { // If the end node of the connection is not visited.
                V[v] = true; // Mark the end node as visited.
                D[v] = D[u] + 1; // Set the distance from the start node to the end node to the distance from the start node to the start node of the connection plus 1.
                A[v] = u; // Set the parent of the end node to the start node of the connection.
                Q.push(v); // Push the end node to the queue.
            }
        }
    }

    // IMPLEMENT BFS ALGORITHM.
}

void Graph::eulerianCycle(int startNodeIndex)
{
    // IMPLEMENT EULERIAN CYCLE ALGORITHM.
}

void Graph::dijkstra(int startNodeIndex)
{
  int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<Node*> nodes = this->nodes; // Vector of nodes in the graph.
    int D[numberOfVertices]; // Array of distanceD[i] = numeric_limitD[i] = numeric_limits<int>::max(); // Initialize with infinity.s<int>::max(); // Initialize with infinity.s from the start node.
    int* A = new int[numberOfVertices]; // Array of parent nodes.
    vector<bool> C(numberOfVertices, false); // Vector of visited nodes.

    for (int i = 0; i <= numberOfVertices; i++) {
        D[i] = numeric_limits<int>::max(); // Initialize with infinity.
        A[i] = -1; // Initialize with -1.
    }

    D[startNodeIndex] = 0; // Set the distance from the start node to itself to 0.
    A[startNodeIndex] = -1; // Set the parent of the start node to -1.
    
    vector<HeapNode*> heapNodes = vector<HeapNode*>(); // Vector of heap nodes.
    MinHeap minHeap = MinHeap(heapNodes); // Create a min heap.
    for (int n = 0; n < numberOfVertices; n++) {
        minHeap.insert(nodes[n], D[n]); // Insert the nodes to the min heap.
    }

    while (find(C.begin(), C.end(), false) != C.end()) {
        Node* u = minHeap.popMin();
        C[u->getNumber()] = true;

        for (vector<Connection*>::iterator it = u->getConnections().begin(); it != u->getConnections().end(); ++it) { // Iterate through the connections (neighbors) of the node.
            Node* v = (*it)->getEndNode(); // Get the end node of the connection.
            int w = (*it)->getWeight(); // Get the weight of the connection.

            if (D[v->getNumber()] > D[u->getNumber()] + w) { // If the distance from the start node to the end node is greater than the distance from the start node to the start node of the connection plus the weight of the connection.
                D[v->getNumber()] = D[u->getNumber()] + w; // Set the distance from the start node to the end node to the distance from the start node to the start node of the connection plus the weight of the connection.
                A[v->getNumber()] = u->getNumber(); // Set the parent of the end node to the start node of the connection.
            }
        }
    }
}

void Graph::flowdWarshall()
{
    // IMPLEMENT FLOYD WARSHALL ALGORITHM.
}

void Graph::addNode(Node* node)
{
    this->nodes.push_back(node);
    this->numberOfVertices++;
}

void Graph::addEdge(Node* startNode, Node* endNode, int weight)
{
    Connection* connection = new Connection(weight, startNode, endNode, true);
    startNode->addConnection(connection);
    endNode->addConnection(connection);
    this->numberOfEdges++;
}

void Graph::addArc(Node* startNode, Node* endNode, int weight)
{
    Connection* connection = new Connection(weight, startNode, endNode, false);

    startNode->addConnection(connection);
    this->numberOfArcs++;
}

Graph::~Graph()
{
    for (int nodeIndex = 0; nodeIndex < this->nodes.size(); nodeIndex++)
    {
        delete this->nodes[nodeIndex];
    }
}
