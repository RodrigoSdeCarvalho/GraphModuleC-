#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <memory>

#include "Graph/AbstractGraph.h"
#include "Graph/Node.h"
#include "Graph/Connection.h"

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
    nodeKeys.reserve(this->nodes.size());
    for (auto & node : this->nodes)
        {
            nodeKeys.push_back(node->getNumber());
        }
    return nodeKeys;
}

vector<shared_ptr<Node>> AbstractGraph::getNodes()
{
    return this->nodes;
}

void AbstractGraph::addNode(const shared_ptr<Node>& node)
{
    this->nodes.push_back(node);
    this->numberOfVertices++;
}

void AbstractGraph::showNodes()
{
    for (auto & node : this->nodes)
    {
        cout << "Vertex name " << node->getName() << " with number " << node->getNumber() << endl;
    }
}

AbstractGraph::~AbstractGraph()
= default;
