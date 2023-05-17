#include <iostream>
#include <vector>
#include <tuple>
#include <memory>

#include "Graph/Node.h"
#include "Graph/Connection.h"

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
    for (auto & connection : this->connections)
    {
        connectionsToReturn.push_back(connection.lock());
    }

    return connectionsToReturn;
}

void Node::addConnections(const vector<weak_ptr<Connection>>& connectionsToAdd)
{
    for (const auto & connIndex : connectionsToAdd)
    {
        this->addConnection(connIndex);
    }
}

void Node::addConnection(const weak_ptr<Connection>& connectionToAdd)
{
    this->connections.push_back(connectionToAdd);
}

tuple<bool, shared_ptr<Connection>> Node::getConnectionWith(const shared_ptr<Node>& NodeConnectedOnTheOtherEnd)
{    
    for (int connIndex = 0; connIndex < this->connections.size(); connIndex++)
    {
        weak_ptr<Connection> conn = this->connections[connIndex];

        shared_ptr<Node> endNode = (conn.lock())->getEndNode();

        //cout << "\tChecking if " << this->number << " has connection with " << endNode->getNumber() << ": ";

        if ((endNode->getNumber() == NodeConnectedOnTheOtherEnd->getNumber()))
        {
            //cout << "YES! node connected: "<< NodeConnectedOnTheOtherEnd->getNumber()<<endl;
            return make_tuple(true, conn.lock());
        }
        else
        {
            if (connIndex == this->connections.size() - 1)
            {
                //cout << "NO! node connected: "<< NodeConnectedOnTheOtherEnd->getNumber()<<endl;
                return make_tuple(false, nullptr);
            }
            //cout << "NO! node connected: "<< NodeConnectedOnTheOtherEnd->getNumber()<<endl;
            continue;
        }
    }
    return {};
}

shared_ptr<Connection> Node::getOutgoingConnectionTo(const shared_ptr<Node>& NodeConnectedOnTheOtherEnd)
{
    for (const auto& conn : this->outgoingConnections)
    {
        shared_ptr<Node> endNode = (conn.lock())->getEndNode();

        if (endNode == NodeConnectedOnTheOtherEnd)
        {
            return conn.lock();
        }
    }
    return {};
}

vector<shared_ptr<Node>> Node::getNeighbours()
{
    vector<shared_ptr<Node>> neighbours;

    for (const auto& conn : this->connections)
    {
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
    for (const auto & incomingConnection : this->incomingConnections)
    {
        incomingConnectionsToReturn.push_back(incomingConnection.lock());
    }

    return incomingConnectionsToReturn;
}

vector<shared_ptr<Connection>> Node::getOutgoingConnections()
{
    vector <shared_ptr<Connection>> outgoingConnectionsToReturn = vector<shared_ptr<Connection>>();
    for (const auto & outgoingConnection : this->outgoingConnections)
    {
        outgoingConnectionsToReturn.push_back(outgoingConnection.lock());
    }

    return outgoingConnectionsToReturn;
}

void Node::addIncomingConnection(const weak_ptr<Connection>& connectionToAdd)
{
    this->incomingConnections.push_back(connectionToAdd);
}

void Node::addOutgoingConnection(const weak_ptr<Connection>& connectionToAdd)
{
    this->outgoingConnections.push_back(connectionToAdd);
}

vector<shared_ptr<Node>> Node::getOutgoingNeighbours()
{
    vector<shared_ptr<Node>> neighbours;

    for (const auto& conn : this->outgoingConnections)
    {
        shared_ptr<Node> endNode = (conn.lock())->getEndNode();

        neighbours.push_back(endNode);
    }

    return neighbours;
}

vector<tuple<shared_ptr<Node>, shared_ptr<Connection>>> Node::getOutgoingNeighboursWithConnection()
{
    vector<tuple<shared_ptr<Node>, shared_ptr<Connection>>> neighbours;

    for (const auto& conn : this->outgoingConnections)
    {
        shared_ptr<Node> endNode = (conn.lock())->getEndNode();

        neighbours.emplace_back(endNode, conn.lock());
    }

    return neighbours;
}

vector<shared_ptr<Node>> Node::getIncomingNeighbours()
{
    vector<shared_ptr<Node>> neighbours;

    for (const auto& conn : this->incomingConnections)
    {
        shared_ptr<Node> startNode = (conn.lock())->getStartNode();

        neighbours.push_back(startNode);
    }

    return neighbours;
}

Node::~Node() 
= default;
