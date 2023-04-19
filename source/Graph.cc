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
#include "HeapNode.h"

using namespace std;
using namespace GraphModule;

Graph::Graph(string inputFilePath)
{
    this->numberOfVertices = 0;
    this->numberOfEdges = 0;
    this->numberOfArcs = 0;

    this->buildGraphFromInputFile(inputFilePath);
}

int Graph::getNumberOfVertices()
{
    return this->numberOfVertices;
}

vector<int> Graph::getNodeKeys()
{
    vector<int> nodeKeys;
    for (int i = 0; i < this->nodes.size(); i++)
    {
        nodeKeys.push_back(this->nodes[i]->getNumber());
    }
    return nodeKeys;
}

vector<Node*> Graph::getNodes()
{
    return this->nodes;
}

void Graph::buildGraphFromInputFile(string inputFilePath) //TEST THIS PROPERLY.
{
    cout << "BUILDING GRAPH FROM INPUT FILE" << inputFilePath << endl;
    char* inputFilePathChar = &inputFilePath[0];
    cout << "INPUT FILE PATH CHAR: " << inputFilePathChar << endl;
    ifstream inputFile;

    inputFile.open(inputFilePathChar, ios::in);

    bool inputVertices = false;
    bool inputEdges = false;
    bool inputArcs = false;

    if (inputFile.is_open())
    {   
        cout << "FILE OPENED" << endl;
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
    cout << "BFS START 0" << endl;
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<Node*> nodes = this->nodes; // Vector of nodes in the graph.
    bool *V = new bool[numberOfVertices]; // Array of visited nodes.
    int D[numberOfVertices]; // Array of distances from the start node.
    int *A = new int[numberOfVertices]; // Array of parent nodes.
    cout << "BFS START 1" << endl;
    for (int i = 0; i <= numberOfVertices; i++) {
        V[i] = false; // Initialize with false.
        D[i] = numeric_limits<int>::max(); // Initialize with infinity.
        A[i] = -1; // Initialize with -1.
    }
    cout << "BFS START 2" << endl;
    V[startNodeIndex] = true; // Mark the start node as visited.
    D[startNodeIndex] = 0; // Set the distance from the start node to itself to 0.
    A[startNodeIndex] = -1; // Set the parent of the start node to -1.

    queue<int> Q; // Create a queue.
    Q.push(startNodeIndex); // Push the start node to the queue.
    cout << "BFS START 3" << endl;
    while (!Q.empty())
    {
        cout << "BFS START 3.1" << endl;
        int u = Q.front(); // Get the first element in the queue.
        Q.pop(); // Remove the first element in the queue.
        cout << "BFS START 3.2" << endl;
        vector<Connection*> connections = nodes[u]->getConnections(); // Get the connections of the start node.
        for (int i = 0; i != connections.size(); ++i)
        {
            Connection* conn = connections[i];
            cout << "BFS START 3.3" << endl;
            Node* vNode = (conn)->getEndNode(); // Get the end node of the connection.
            cout << "BFS START 3.3.1" << endl;
            int v = vNode->getNumber() - 1; // Get the index of the end node of the connection.
            if (!V[v]) { // If the end node of the connection is not visited.
                cout << "BFS START 3.3.1.1" << endl;
                V[v] = true; // Mark the end node as visited.
                cout << "BFS START 3.3.1.2" << endl;
                D[v] = D[u] + 1; // Set the distance from the start node to the end node to the distance from the start node to the start node of the connection plus 1.
                cout << "BFS START 3.3.1.3" << endl;
                A[v] = u; // Set the parent of the end node to the start node of the connection.
                cout << "BFS START 3.3.1.4" << endl;
                Q.push(v); // Push the end node to the queue.
                cout << "BFS START 3.3.1.5" << endl;
            }
        }
    }
    cout << "BFS START 4" << endl;
    for (int n= 0; n < numberOfVertices; n++)
    {
        cout << "BFS Called to \n" << startNodeIndex << endl;
        cout << D[n] << ": " << n << endl;
    }
}

void Graph::eulerianCycle(int startNodeIndex)
{
    // IMPLEMENT EULERIAN CYCLE ALGORITHM.
}

void Graph::dijkstra(int startNodeIndex)
{
    cout << "Dijkstra Called to \n" << startNodeIndex << endl;
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<Node*> nodes = this->nodes; // Vector of nodes in the graph.
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

    vector<HeapNode*> heapNodes = vector<HeapNode*>(numberOfVertices);    
    for (int n = 0; n < numberOfVertices; n++)
    {
        heapNodes[n] = new HeapNode(n, nodes[n], D[n]);
    }
    MinHeap minHeap = MinHeap(heapNodes); // Create a min heap.

    while (visitedNodes < numberOfVertices)
    {
        cout << "Visited nodes: " << visitedNodes << endl;
        Node* u = minHeap.popMin();
        cout << "Popped node: " << u->getNumber() << endl;
        C[u->getNumber()] = true;
        visitedNodes++;

        for (vector<Connection*>::iterator it = u->getConnections().begin(); it != u->getConnections().end(); ++it)
        {
            cout << "Connection: " << (*it)->getStartNode()->getNumber() << " -> " << (*it)->getEndNode()->getNumber() << " (" << (*it)->getWeight() << ")" << endl;
            Node* v = (*it)->getEndNode();
            int w = (*it)->getWeight();

            if (D[v->getNumber()] > D[u->getNumber()] + w) {
                D[v->getNumber()] = D[u->getNumber()] + w;
                A[v->getNumber()] = u->getNumber();
            }
        }
    }

    cout << "Dijkstra finished" << endl;
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
