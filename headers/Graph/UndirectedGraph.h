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

            vector<int> prim();

            void printPrim(vector<int> A);

            vector<int> coloring();

            void printColoring(vector<int>  colors);

            void configureBipartiteGraph();
            
            int hopcroftKarp();

            bool bipartiteGraphDFS(int u);

            bool bipartiteGraphBFS();
            
            void printHopcroftKarp(int maximum_matching);

            ~UndirectedGraph() override;

        private:
            int numberOfEdges;
            vector<shared_ptr<Connection>> edges;
            list<pair<int, float> > *adj; //used for Prim
            list<int> *color_adj; //used for Coloring 
            
            // Varibles below used on hopcroftKarp
            list<int> *adjacency;
            int m = 0;
            int n = 0;
            int *pairU, *pairV, *dist;
    };
}

#endif