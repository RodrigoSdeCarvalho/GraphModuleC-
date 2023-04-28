#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <algorithm>
#include <memory>

#include "AbstractGraph.h"
#include "Node.h"
#include "Connection.h"
#include "MinHeap.h"
#include "HeapNode.h"

using namespace std;
using namespace GraphModule;

AbstractGraph::AbstractGraph()
{
    this->numberOfVertices = 0;
}

int AbstractGraph::getNumberOfVertices()
{
    return this->numberOfVertices;
}

vector<int> AbstractGraph::getNodeKeys()
{
    vector<int> nodeKeys;
    for (int i = 0; i < this->nodes.size(); i++)
    {
        nodeKeys.push_back(this->nodes[i]->getNumber());
    }
    return nodeKeys;
}

vector<shared_ptr<Node>> AbstractGraph::getNodes()
{
    return this->nodes;
}

void AbstractGraph::addNode(shared_ptr<Node> node)
{
    this->nodes.push_back(node);
    this->numberOfVertices++;
}

void AbstractGraph::showNodes()
{
    for (int i = 0; i < this->nodes.size(); i++)
    {
        cout << "Vertex name " << this->nodes[i]->getName() << " with number " << this->nodes[i]->getNumber() << endl;
    }
}

AbstractGraph::~AbstractGraph()
{
    
}
