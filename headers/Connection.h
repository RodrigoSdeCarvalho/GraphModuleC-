#ifndef Connection_h
#define Connection_h

#include <iostream>
#include <vector>
#include <tuple>
#include <memory>

using namespace std;

namespace GraphModule
{
    class Node;

    class Connection
    {
        public:
            Connection(float weight, shared_ptr<Node> startNode, shared_ptr<Node> endNode, bool goesBothWays);

            float getWeight();
            shared_ptr<Node> getStartNode();
            shared_ptr<Node> getEndNode();
            bool getGoesBothWays();

            void setWeight(float weight);
            void setGoesBothWays(bool goesBothWays);

            tuple<shared_ptr<Node>, shared_ptr<Node>> getNodes();

            ~Connection();

        private:
            float weight;
            shared_ptr<Node> startNode;
            shared_ptr<Node> endNode;
            bool goesBothWays;
    };
}

#endif
