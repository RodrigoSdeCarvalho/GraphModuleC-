#include <iostream>
#include <vector>
#include <string>

#include "Graph.h"
#include "Node.h"

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
}

void Graph::flowdWarshall()
{
    // IMPLEMENT FLOYD WARSHALL ALGORITHM.
}
