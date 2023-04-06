#ifndef Node_h
#define Node_h

#include <iostream>
#include <vector> // Will perhaps be replaced by list if adds and removes are more common than reads. Vector is cache friendly.
#include <tuple>

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

            vector<Connection*> getConnections();

            void addConnections(vector<Connection*> connectionsToAdd);

            Connection* getConnectionWith(Node* NodeConnectedOnTheOtherEnd);

            Connection* getOutgoingConnectionTo(Node* NodeConnectedOnTheOtherEnd);

            vector<Node*> getNeighbours();

            vector<Connection*> getIncomingConnections();

            vector<Connection*> getOutgoingConnections();

            void addConnection(Connection* connectionToAdd);

            void addIncomingConnection(Connection* connectionToAdd);

            void addOutgoingConnection(Connection* connectionToAdd);

            vector<Node*> getOutgoingNeighbours();

            vector<tuple<Node*, Connection*>> getOutgoingNeighboursWithConnection();

            vector<Node*> getIncomingNeighbours();

            ~Node();    

        private:
            int number;
            string name;
            vector<Connection*> connections;
            vector<Connection*> incomingConnections;
            vector<Connection*> outgoingConnections;
    };
}

#endif 
