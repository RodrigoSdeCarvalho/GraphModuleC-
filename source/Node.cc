#include <iostream>
#include <vector> // Will perhaps be replaced by list if adds and removes are more common than reads. Vector is cache friendly.
#include <tuple>
#include "../headers/Node.h"

using namespace std;
using namespace GraphModule;

Node::Node(int number, string name)
{
    this->number = number;
    this->name = name;
}

int Node::getNumber()
{
    return number;
}

string Node::getName()
{
    return name;
}

vector<Connection*> Node::getConnections()
{
    return connections;
}
