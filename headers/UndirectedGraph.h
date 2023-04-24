#ifndef UndirectedGraph_h
#define UndirectedGraph_h

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

    class UndirectedGraph : public AbstractGraph
    {
        public:
            UndirectedGraph();

            int getDegreeOfNode(int nodeKey);

            void addEdge(shared_ptr<Node> node1, shared_ptr<Node> node2, int weight);

            void BFS(int startNodeIndex);

            void eulerianCycle(int startNodeIndex);

            void dijkstra(int startNodeIndex);

            void floydWarshall(int startNodeIndex);

            ~UndirectedGraph();

        private:
            int numberOfEdges;
            vector<shared_ptr<Connection>> edges;
    };
}

#endif