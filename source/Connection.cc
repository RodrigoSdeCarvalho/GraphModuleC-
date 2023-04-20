#include <iostream>
#include <vector>
#include <tuple>
#include "Connection.h"
#include <tuple>
#include <memory>

#include "Node.h"

using namespace std;
using namespace GraphModule;

Connection::Connection(float weight, shared_ptr<Node> startNode, shared_ptr<Node> endNode, bool goesBothWays)
{
    this->weight = weight;
    this->startNode = startNode;
    this->endNode = endNode;
    this->goesBothWays = goesBothWays;
}

float Connection::getWeight()
{
    return this->weight;
}

shared_ptr<Node> Connection::getStartNode()
{
    return this->startNode;
}

shared_ptr<Node> Connection::getEndNode()
{
    return this->endNode;
}

bool Connection::getGoesBothWays()
{
    return this->goesBothWays;
}

void Connection::setWeight(float weight)
{
    this->weight = weight;
}

void Connection::setGoesBothWays(bool goesBothWays)
{
    this->goesBothWays = goesBothWays;
}

//Be careful for bugs. This function is not tested.
tuple<shared_ptr<Node>, shared_ptr<Node>> Connection::getNodes()
{
    return make_tuple(this->startNode, this->endNode);
}

Connection::~Connection()
{
    
}
