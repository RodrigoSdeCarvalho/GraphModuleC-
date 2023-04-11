#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace GraphModule
{
    class Node;    

    class Graph
    {
        public:
            Graph(string nodesFilePath);

            vector<Node*> buildGraphFromInputFile(string nodesFilePath);

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
