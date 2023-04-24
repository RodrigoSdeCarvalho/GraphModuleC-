#ifndef DirectedGraph_h
#define DirectedGraph_h

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "AbstractGraph.h"

using namespace std;

namespace GraphModule
{
    class Node;
    class Connection;

    class DirectedGraph : public AbstractGraph
    {
        public:
            DirectedGraph();
        
            int getDegreeOfNode(int nodeKey);

            int getInDegreeOfNode(int nodeKey);

            int getOutDegreeOfNode(int nodeKey);

            void addArc(shared_ptr<Node> startNode, shared_ptr<Node> endNode, int weight);

            ~DirectedGraph();

            //ADD METHODS FOR A2 AND A3 HERE.

        private:
            int numberOfArcs;
            vector<shared_ptr<Connection>> arcs;
    };
}

#endif