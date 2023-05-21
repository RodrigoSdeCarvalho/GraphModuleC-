#ifndef UndirectedGraph_h
#define UndirectedGraph_h

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <tuple>
#include <list>

#include "Graph/AbstractGraph.h"

using namespace std;

typedef pair<int, float> node_weight_pair; // node_weight_pair ==>  Integer Pair

namespace GraphModule
{
    class Node;
    class Connection;

    class UndirectedGraph : public AbstractGraph
    {
        public:
            UndirectedGraph();

            int getDegreeOfNode(int nodeKey) override;

            void addEdge(const shared_ptr<Node>& node1, const shared_ptr<Node>& node2, float weight);

            tuple<vector<int>, vector<int>> BFS(int startNodeIndex);

            void printBFS(vector<int> D);

            vector<int> eulerianCycle(int startNodeIndex);

            tuple<bool, vector<int>, vector<vector<int>>> searchEulerianSubcycle(int beginNodeIndex, vector<vector<int>> C);

            void printEulerianCycle(vector<int> Cycle);

            tuple<vector<int>, vector<int>> dijkstra(int startNodeIndex);

            void printDijkstra(int startNodeIndex, vector<int> D, vector<int> A);

            vector<vector<int>> floydWarshall();

            void printFloydWarshall(vector<vector<int>> D);

            vector<vector<int>> kruskal();

            void printKruskal(const vector<vector<int>>& A);

            vector<int> prim();

            void printPrim(vector<int> A);

            ~UndirectedGraph() override;

        private:
            int numberOfEdges;
            vector<shared_ptr<Connection>> edges;
            list<pair<int, float> > *adj;
    };
}

#endif