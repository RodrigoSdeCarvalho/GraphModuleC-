#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Graph.h"
#include "Node.h"
#include "Connection.h"

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
    // IMPLEMENT BFS ALGORITHM.
}

void Graph::eulerianCycle(int startNodeIndex)
{
    // IMPLEMENT EULERIAN CYCLE ALGORITHM.
}

void Graph::dijkstra(int startNodeIndex)
{
    // IMPLEMENT DIJKSTRA ALGORITHM.
    // ALLOCATE MINHEAP FROM MINHEAP.H, AND DELETE IT WHEN DONE, TO AVOID MEMORY LEAKS.
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
