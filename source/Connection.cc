#include <iostream>
#include <vector>
#include <tuple>
#include "../headers/Connection.h"

using namespace std;
using namespace GraphModule;

Connection::Connection(float weight, Node* startNode, Node* endNode, bool goesBothWays)
{
    this->weight = weight;
    this->startNode = startNode;
    this->endNode = endNode;
    this->goesBothWays = goesBothWays;
}
