#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <vector>
#include "Node.h"
#include "Connection.h"

namespace GraphModule
{
    class Graph
    {
        public:
            Graph(string nodesFilePath);

            void BFS(int startNodeIndex);

            void eulerianCycle(int startNodeIndex);

            void dijkstra(int startNodeIndex);

            void flowdWarshall();

            ~Graph();

        private:
            int numberOfVertices;
            int numberOfEdges;
            vector<Node*> nodes;
    };
}

#endif