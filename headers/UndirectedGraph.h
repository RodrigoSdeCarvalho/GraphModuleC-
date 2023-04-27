#ifndef UndirectedGraph_h
#define UndirectedGraph_h

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <tuple>

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

            tuple<vector<int>, vector<int>> BFS(int startNodeIndex);

            void printBFS(int startNodeIndex, vector<int> D, vector<int> A);

            void eulerianCycle(int startNodeIndex);

            tuple<bool, vector<int>> searchEulerianSubcycle(int beginNodeIndex, vector<vector<int>> C);

            tuple<vector<int>, vector<int>> dijkstra(int startNodeIndex);

            void printDijkstra(int startNodeIndex, vector<int> D, vector<int> A);

            void floydWarshall(int startNodeIndex);

            ~UndirectedGraph();

        private:
            int numberOfEdges;
            vector<shared_ptr<Connection>> edges;
    };
}

#endif