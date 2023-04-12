#include <iostream>
#include <vector>
#include <string>

#include "Graph.h"
#include "Node.h"
#include "Connection.h"

using namespace std;
using namespace GraphModule;

Graph::Graph(string nodesFilePath)
{
    this->numberOfVertices = 0;
    this->numberOfVertices = 0;
    this->numberOfEdges = 0;

    this->nodes = this->buildGraphFromInputFile(nodesFilePath);
}

vector<Node*> Graph::buildGraphFromInputFile(string nodesFilePath)
{
    // IMPLEMENT READ FROM FILE. ADD NODES AND CONNECTIONS TO THE GRAPH.
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

void Graph::addArc(Node* startNode, Node* endNode, int weight, bool goesBothWays)
{
    Connection* connection = new Connection(weight, startNode, endNode, goesBothWays);

    if (goesBothWays)
    {
        startNode->addConnection(connection);
        endNode->addConnection(connection);
        this->numberOfArcs++;
    }
    else
    {
        startNode->addConnection(connection);
        this->numberOfArcs++;
    }
}

Graph::~Graph()
{
    for (int nodeIndex = 0; nodeIndex < this->nodes.size(); nodeIndex++)
    {
        delete this->nodes[nodeIndex];
    }
}
