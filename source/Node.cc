#include <iostream>
#include <vector>
#include <tuple>
#include <memory>

#include "Node.h"
#include "Connection.h"

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

vector<shared_ptr<Connection>> Node::getConnections()
{
    vector<shared_ptr<Connection>> connectionsToReturn = vector<shared_ptr<Connection>>();
    for (int connIndex = 0; connIndex < this->connections.size(); connIndex++)
    {
        connectionsToReturn.push_back((this->connections[connIndex]).lock());
    }

    return connectionsToReturn;
}

void Node::addConnections(vector<weak_ptr<Connection>> connectionsToAdd)
{
    for (int connIndex = 0; connIndex < connectionsToAdd.size(); connIndex++)
    {
        this->addConnection(connectionsToAdd[connIndex]);
    }
}

void Node::addConnection(weak_ptr<Connection> connectionToAdd)
{
    this->connections.push_back(connectionToAdd);
}

tuple<bool, shared_ptr<Connection>> Node::getConnectionWith(shared_ptr<Node> NodeConnectedOnTheOtherEnd)
{
    for (int connIndex = 0; connIndex < this->connections.size(); connIndex++)
    {
        weak_ptr<Connection> conn = this->connections[connIndex];

        shared_ptr<Node> startNode = (conn.lock())->getStartNode();
        shared_ptr<Node> endNode = (conn.lock())->getEndNode();

        if ((startNode->getNumber() == NodeConnectedOnTheOtherEnd->getNumber()) || (endNode->getNumber() == NodeConnectedOnTheOtherEnd->getNumber()))
        {
            return make_tuple(true, conn.lock());
        }
        else
        {
            return make_tuple(false, nullptr);
        }
    }
}

shared_ptr<Connection> Node::getOutgoingConnectionTo(shared_ptr<Node> NodeConnectedOnTheOtherEnd)
{
    for (int connIndex = 0; connIndex < this->outgoingConnections.size(); connIndex++)
    {
        weak_ptr<Connection> conn = this->outgoingConnections[connIndex];

        shared_ptr<Node> endNode = (conn.lock())->getEndNode();

        if (endNode == NodeConnectedOnTheOtherEnd)
        {
            return conn.lock();
        }
    }
}

vector<shared_ptr<Node>> Node::getNeighbours()
{
    vector<shared_ptr<Node>> neighbours;

    for (int connIndex = 0; connIndex < this->connections.size(); connIndex++)
    {
        weak_ptr<Connection> conn = this->connections[connIndex];

        shared_ptr<Node> startNode = (conn.lock())->getStartNode();
        shared_ptr<Node> endNode = (conn.lock())->getEndNode();

        if (startNode.get() == this)
        {
            neighbours.push_back(endNode);
        }
        else if (endNode.get() == this)
        {
            neighbours.push_back(startNode);
        }
    }

    return neighbours;
}

vector<shared_ptr<Connection>> Node::getIncomingConnections()
{
    vector<shared_ptr<Connection>> incomingConnectionsToReturn = vector<shared_ptr<Connection>>();
    for (int connIndex = 0; connIndex < this->incomingConnections.size(); connIndex++)
    {
        incomingConnectionsToReturn.push_back(this->incomingConnections[connIndex].lock());
    }

    return incomingConnectionsToReturn;
}

vector<shared_ptr<Connection>> Node::getOutgoingConnections()
{
    vector <shared_ptr<Connection>> outgoingConnectionsToReturn = vector<shared_ptr<Connection>>();
    for (int connIndex = 0; connIndex < this->outgoingConnections.size(); connIndex++)
    {
        outgoingConnectionsToReturn.push_back(this->outgoingConnections[connIndex].lock());
    }

    return outgoingConnectionsToReturn;
}

void Node::addIncomingConnection(weak_ptr<Connection> connectionToAdd)
{
    this->incomingConnections.push_back(connectionToAdd);
}

void Node::addOutgoingConnection(weak_ptr<Connection> connectionToAdd)
{
    this->outgoingConnections.push_back(connectionToAdd);
}

vector<shared_ptr<Node>> Node::getOutgoingNeighbours()
{
    vector<shared_ptr<Node>> neighbours;

    for (int connIndex = 0; connIndex < this->outgoingConnections.size(); connIndex++)
    {
        weak_ptr<Connection> conn = this->outgoingConnections[connIndex];

        shared_ptr<Node> endNode = (conn.lock())->getEndNode();

        neighbours.push_back(endNode);
    }

    return neighbours;
}

vector<tuple<shared_ptr<Node>, shared_ptr<Connection>>> Node::getOutgoingNeighboursWithConnection()
{
    vector<tuple<shared_ptr<Node>, shared_ptr<Connection>>> neighbours;

    for (int connIndex = 0; connIndex < this->outgoingConnections.size(); connIndex++)
    {
        weak_ptr<Connection> conn = this->outgoingConnections[connIndex];

        shared_ptr<Node> endNode = (conn.lock())->getEndNode();

        neighbours.push_back(make_tuple(endNode, conn.lock()));
    }

    return neighbours;
}

vector<shared_ptr<Node>> Node::getIncomingNeighbours()
{
    vector<shared_ptr<Node>> neighbours;

    for (int connIndex = 0; connIndex < this->incomingConnections.size(); connIndex++)
    {
        weak_ptr<Connection> conn = this->incomingConnections[connIndex];

        shared_ptr<Node> startNode = (conn.lock())->getStartNode();

        neighbours.push_back(startNode);
    }

    return neighbours;
}

Node::~Node() 
{

}
