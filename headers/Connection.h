#ifndef Connection_h
#define Connection_h

#include <iostream>
#include <vector>
#include "Node.h"

using namespace std;

namespace GraphModule
{
    class Graph::Connection
    {
        public:
            Connection(float weight, Node* startNode, Node* endNode, bool goesBothWays);

            float getWeight();
            Node* getStartNode();
            Node* getEndNode();
            bool getGoesBothWays();

            void setWeight(float weight);
            void setGoesBothWays(bool goesBothWays);

            tuple<Node*, Node*> getNodes();

            ~Connection();

        private:
            float weight;
            Node* startNode;
            Node* endNode;
            bool goesBothWays;
    };
}

#endif
