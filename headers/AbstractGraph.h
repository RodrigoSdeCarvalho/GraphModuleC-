#ifndef AbstractGraph_h
#define AbstractGraph_h

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

namespace GraphModule
{
    class Node;
    class Connection;

    class AbstractGraph
    {
        public:
            AbstractGraph();

            int getNumberOfVertices();

            vector<int> getNodeKeys();

            vector<shared_ptr<Node>> getNodes();

            virtual int getDegreeOfNode(int nodeKey) = 0;

            void addNode(shared_ptr<Node> node);

            void showNodes();

            virtual ~AbstractGraph();

        protected:
            int numberOfVertices;
            vector<shared_ptr<Node>> nodes;
    };
}

#endif
