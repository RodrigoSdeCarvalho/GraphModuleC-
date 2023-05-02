#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <algorithm>
#include <memory>

#include "DirectedGraph.h"
#include "AbstractGraph.h"
#include "Node.h"
#include "Connection.h"
#include "MinHeap.h"
#include "HeapNode.h"

using namespace std;
using namespace GraphModule;

DirectedGraph::DirectedGraph()
{
    this->numberOfArcs = 0;
}

int DirectedGraph::getDegreeOfNode(int nodeKey)
{
    shared_ptr<Node> node = this->nodes[nodeKey];

    return (node->getIncomingConnections()).size() + (node->getOutgoingConnections()).size();
}

int DirectedGraph::getInDegreeOfNode(int nodeKey)
{
    shared_ptr<Node> node = this->nodes[nodeKey];

    return (node->getIncomingConnections()).size();
}

int DirectedGraph::getOutDegreeOfNode(int nodeKey)
{
    shared_ptr<Node> node = this->nodes[nodeKey];

    return (node->getOutgoingConnections()).size();
}

vector<vector<int>> DirectedGraph::stronglyConnectedComponents()
{

}

tuple<vector<bool>,vector<int>,vector<int>,vector<int>> DirectedGraph::DFS()
{

}

tuple<vector<bool>,vector<int>,vector<int>,vector<int>, int> DirectedGraph::DFSVisit(vector<bool> C,vector<int> A,vector<int> T, vector<int> F, int time)
{

}

void DirectedGraph::printStronglyConnectedComponents(vector<vector<int>> A)
{

}

vector<int> DirectedGraph::topologicalSorting()
{

}

tuple<int, vector<bool>, vector<int>, vector<int>, vector<int>, int> DirectedGraph::DFSVisitTopologicalSorting(int v, vector<bool> C, vector<int> F, vector<int> T, vector<int> O, int time)
{

}

void DirectedGraph::printTopologicalSorting(vector<int> O)
{

}

void DirectedGraph::addArc(shared_ptr<Node> startNode, shared_ptr<Node> endNode, int weight)
{
    weak_ptr<Node> startNodeWeakPtr(startNode);
    weak_ptr<Node> endNodeWeakPtr(endNode);

    shared_ptr<Connection> connectionSharedPtr = make_shared<Connection>(weight, startNodeWeakPtr, endNodeWeakPtr, false);
    this->arcs.push_back(connectionSharedPtr);
    
    weak_ptr<Connection> connectionWeakPtr(connectionSharedPtr);
    startNode->addOutgoingConnection(connectionWeakPtr);
    endNode->addIncomingConnection(connectionWeakPtr);

    this->numberOfArcs++;
}

DirectedGraph::~DirectedGraph()
{

}
