#ifndef Node_h
#define Node_h

#include <iostream>
#include <vector> // Will perhaps be replaced by list if adds and removes are more common than reads. Vector is cache friendly.
#include <tuple>
#include <memory>

using namespace std;

namespace GraphModule
{

    class Connection;

    class Node
    {
        public:
            Node(int number, string name);

            int getNumber();

            string getName();

            vector<shared_ptr<Connection>> getConnections();

            void addConnections(const vector<weak_ptr<Connection>>& connectionsToAdd);

            tuple<bool, shared_ptr<Connection>> getConnectionWith(const shared_ptr<Node>& NodeConnectedOnTheOtherEnd);

            shared_ptr<Connection> getOutgoingConnectionTo(const shared_ptr<Node>& NodeConnectedOnTheOtherEnd);

            vector<shared_ptr<Node>> getNeighbours();

            vector<shared_ptr<Connection>> getIncomingConnections();

            vector<shared_ptr<Connection>> getOutgoingConnections();

            int numberOfIncomingConnections();

            int numberOfOutgoingConnections();

            void addConnection(const weak_ptr<Connection>& connectionToAdd);

            void addIncomingConnection(const weak_ptr<Connection>& connectionToAdd);

            void addOutgoingConnection(const weak_ptr<Connection>& connectionToAdd);

            vector<shared_ptr<Node>> getOutgoingNeighbours();

            vector<tuple<shared_ptr<Node>, shared_ptr<Connection>>> getOutgoingNeighboursWithConnection();

            vector<shared_ptr<Node>> getIncomingNeighbours();

            ~Node();    

        private:
            int number;
            string name;
            vector<weak_ptr<Connection>> connections;
            vector<weak_ptr<Connection>> incomingConnections;
            vector<weak_ptr<Connection>> outgoingConnections;
    };
}

#endif 
