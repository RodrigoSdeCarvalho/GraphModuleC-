#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

namespace GraphModule
{
    class Node;
    class Connection;

    class Graph
    {
        public:
            Graph(string inputFilePath);

            int getNumberOfVertices();
            
            vector<int> getNodeKeys();

            vector<shared_ptr<Node>> getNodes();

            void buildGraphFromInputFile(string inputFilePath);

            void BFS(int startNodeIndex);

            void eulerianCycle(int startNodeIndex);

            void dijkstra(int startNodeIndex);

            void flowdWarshall();

            void addNode(shared_ptr<Node> node);

            void addEdge(shared_ptr<Node> node1, shared_ptr<Node> node2, int weight);

            void addArc(shared_ptr<Node> startNode, shared_ptr<Node> endNode, int weight);

            ~Graph();

        private:
            int numberOfVertices;
            int numberOfEdges;
            int numberOfArcs;
            vector<shared_ptr<Node>> nodes;
            vector<shared_ptr<Connection>> connections;
    };
}

#endif
