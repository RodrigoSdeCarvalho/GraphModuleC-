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
    tuple<vector<bool>,vector<int>,vector<int>,vector<int>> DFSVectors = this->DFS();

    vector<bool> C = get<0>(DFSVectors);
    vector<int> T = get<1>(DFSVectors);
    vector<int> A = get<2>(DFSVectors);
    vector<int> F = get<3>(DFSVectors);
    int time = 0;

    unique_ptr<DirectedGraph> transposedGraph = buildTransposedGraph();
    //print both graph's arcs for debug

    tuple<vector<bool>,vector<int>,vector<int>,vector<int>, int> DFSVisitVectors = transposedGraph->DFSVisit(C,T,A,F,time);
    
    //verificar qual o data type dessa variável A, deveria ser um vector<vector<int>>, não apenas vector<int>. Talvez todos seja na verdade por serem matrizes 2D.
    //A = get<2>(DFSVisitVectors)
    
    return 


}

unique_ptr<DirectedGraph> DirectedGraph::buildTransposedGraph()
{
    DirectedGraph* graph = new DirectedGraph();
    
    //builds graph with transposed A
    for (int index = 0; index < this->numberOfVertices; index++)
    {   //adds nodes
        shared_ptr<Node> nodeSharedPtr = make_shared<Node>(this->nodes[index]->getNumber(), this->nodes[index]->getName());
        graph->addNode(nodeSharedPtr);
    }
    for (int index = 0; index < this->numberOfArcs; index++)
    {   //adds arcs
        shared_ptr<Node> startNode = this->arcs[index]->getEndNode();
        shared_ptr<Node> endNode = this->arcs[index]->getStartNode();
        int weight = this->arcs[index]->getWeight();
        graph->addArc(startNode, endNode, weight);
    }

    unique_ptr<DirectedGraph> graphUniquePtr(graph);

    return graphUniquePtr;
}

tuple<vector<bool>,vector<int>,vector<int>,vector<int>> DirectedGraph::DFS()
{

    //return make_tuple(C, T, A, F);

}

tuple<vector<bool>,vector<int>,vector<int>,vector<int>, int> DirectedGraph::DFSVisit(vector<bool> C,vector<int> A,vector<int> T, vector<int> F, int time)
{
    //return make_tuple(C, T, A, F);
}

void DirectedGraph::printStronglyConnectedComponents(vector<vector<int>> A)
{
    // "Ao final, imprima na tela as componentes fortemente conexas desse grafo."
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
