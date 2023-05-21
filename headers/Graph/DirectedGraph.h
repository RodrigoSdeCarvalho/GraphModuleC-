#ifndef DirectedGraph_h
#define DirectedGraph_h

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <stack>
#include <memory>
#include "Graph/AbstractGraph.h"

using namespace std;

namespace GraphModule
{
    class Node;
    class Connection;

    class DirectedGraph : public AbstractGraph
    {
        public:
            DirectedGraph();
        
            int getDegreeOfNode(int nodeKey) override;

            int getInDegreeOfNode(int nodeKey);

            int getOutDegreeOfNode(int nodeKey);

            // The main function that finds and prints strongly connected
            // components
            void stronglyConnectedComponents();

            void fillOrder(int v, bool visited[], stack<int> &Stack);

            // A recursive function to print DFS starting from v
            void DFSUtil(int v, bool visited[]);

            // Function that returns reverse (or transpose) of this graph
            unique_ptr<DirectedGraph> getTranspose();

            vector<shared_ptr<Node>> topologicalSorting();

            void DFSVisitTopologicalSorting(int v, vector<bool> &C, vector<int> &F, vector<int> &T, vector<shared_ptr<Node>> &O, int &time);

            void printTopologicalSorting(const vector<shared_ptr<Node>> &O);

            void addArc(const shared_ptr<Node> &startNode, const shared_ptr<Node> &endNode, float weight);

            ~DirectedGraph() override;

            //ADD METHODS FOR A3 HERE.

        private:
            int numberOfArcs;
            vector<shared_ptr<Connection>> arcs;
            list<int> *adj;
    };
}

#endif