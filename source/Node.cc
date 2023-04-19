#include <iostream>
#include <vector>
// Adds are only done when the graph is created and file is read. Reads are done a lot of times during program execution.
// Vector is cache friendly. Hence, reading is better through vector.
#include <tuple>
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

vector<Connection*> Node::getConnections()
{
    return connections;
}

void Node::addConnections(vector<Connection*> connectionsToAdd)
{
    for (int connIndex = 0; connIndex < connectionsToAdd.size(); connIndex++)
    {
        this->addConnection(connectionsToAdd[connIndex]);
    }
}

void Node::addConnection(Connection* connectionToAdd)
{
    this->connections.push_back(connectionToAdd);
}

Connection* Node::getConnectionWith(Node* NodeConnectedOnTheOtherEnd)
{
    for (int connIndex = 0; connIndex < this->connections.size(); connIndex++)
    {
        Connection* conn = this->connections[connIndex];

        Node* startNode = conn->getStartNode();
        Node* endNode = conn->getEndNode();

        if ((startNode == NodeConnectedOnTheOtherEnd) or (endNode == NodeConnectedOnTheOtherEnd))
        {
            return conn;
        }
    }
}

Connection* Node::getOutgoingConnectionTo(Node* NodeConnectedOnTheOtherEnd)
{
    for (int connIndex = 0; connIndex < this->outgoingConnections.size(); connIndex++)
    {
        Connection* conn = this->outgoingConnections[connIndex];

        Node* endNode = conn->getEndNode();

        if (endNode == NodeConnectedOnTheOtherEnd)
        {
            return conn;
        }
    }
}

vector<Node*> Node::getNeighbours()
{
    vector<Node*> neighbours;

    for (int connIndex = 0; connIndex < this->connections.size(); connIndex++)
    {
        Connection* conn = this->connections[connIndex];

        Node* startNode = conn->getStartNode();
        Node* endNode = conn->getEndNode();

        if (startNode == this)
        {
            neighbours.push_back(endNode);
        }
        else if (endNode == this)
        {
            neighbours.push_back(startNode);
        }
    }

    return neighbours;
}

vector<Connection*> Node::getIncomingConnections()
{
    return this->incomingConnections;
}

vector<Connection*> Node::getOutgoingConnections()
{
    return this->outgoingConnections;
}

void Node::addIncomingConnection(Connection* connectionToAdd)
{
    this->incomingConnections.push_back(connectionToAdd);
}

void Node::addOutgoingConnection(Connection* connectionToAdd)
{
    this->outgoingConnections.push_back(connectionToAdd);
}

vector<Node*> Node::getOutgoingNeighbours()
{
    vector<Node*> neighbours;

    for (int connIndex = 0; connIndex < this->outgoingConnections.size(); connIndex++)
    {
        Connection* conn = this->outgoingConnections[connIndex];

        Node* endNode = conn->getEndNode();

        neighbours.push_back(endNode);
    }

    return neighbours;
}

//Be careful for bugs. This function is not tested.
vector<tuple<Node*, Connection*>> Node::getOutgoingNeighboursWithConnection()
{
    vector<tuple<Node*, Connection*>> neighbours;

    for (int connIndex = 0; connIndex < this->outgoingConnections.size(); connIndex++)
    {
        Connection* conn = this->outgoingConnections[connIndex];

        Node* endNode = conn->getEndNode();

        neighbours.push_back(make_tuple(endNode, conn));
    }

    return neighbours;
}

vector<Node*> Node::getIncomingNeighbours()
{
    vector<Node*> neighbours;

    for (int connIndex = 0; connIndex < this->incomingConnections.size(); connIndex++)
    {
        Connection* conn = this->incomingConnections[connIndex];

        Node* startNode = conn->getStartNode();

        neighbours.push_back(startNode);
    }

    return neighbours;
}

Node::~Node() //Look out for memory leaks. This deletes all connections since when an node is deleted, all connections shall be deleted.
{
    if (this->connections.size() > 0)
    {
        for (int connIndex = 0; connIndex < this->connections.size(); connIndex++)
        {
            if (this->connections[connIndex])
            {
                delete this->connections[connIndex];
            }
        }
    }

    if (this->incomingConnections.size() > 0)
    {
        for (int connIndex = 0; connIndex < this->incomingConnections.size(); connIndex++)
        {
            Connection* incomingConnectionsPointer = this->incomingConnections[connIndex];
            if (incomingConnectionsPointer)
            {
                delete incomingConnectionsPointer;
            }
        }
    }

    if (this->outgoingConnections.size() > 0)
    {
        for (int connIndex = 0; connIndex < this->outgoingConnections.size(); connIndex++)
        {
            Connection* outgoingConnectionsPointer = this->outgoingConnections[connIndex];
            if (outgoingConnectionsPointer)
            {
                delete outgoingConnectionsPointer;
            }
        }
    }
}
