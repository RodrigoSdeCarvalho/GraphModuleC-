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
            Graph(string inputFilePath);

            int getNumberOfVertices();
            
            vector<int> getNodeKeys();

            vector<Node*> getNodes();

            void buildGraphFromInputFile(string inputFilePath);

            void BFS(int startNodeIndex);

            void eulerianCycle(int startNodeIndex);

            void dijkstra(int startNodeIndex);

            void flowdWarshall();

            void addNode(Node* node);

            void addEdge(Node* node1, Node* node2, int weight);

            void addArc(Node* startNode, Node* endNode, int weight);

            ~Graph();

        private:
            int numberOfVertices;
            int numberOfEdges;
            int numberOfArcs;
            vector<Node*> nodes;
    };
}

#endif
