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

            vector<vector<int>> stronglyConnectedComponents();

            unique_ptr<DirectedGraph> buildTransposedGraph();
            
            tuple<vector<bool>,vector<int>,vector<int>,vector<int>> DFS();

            tuple<vector<bool>,vector<int>,vector<int>,vector<int>, int> DFSVisit(vector<bool> C,vector<int> A,vector<int> T, vector<int> F, int time);

            void printStronglyConnectedComponents(vector<vector<int>> A);

            vector<int> topologicalSorting();

            tuple<int, vector<bool>, vector<int>, vector<int>, vector<int>, int> DFSVisitTopologicalSorting(int v, vector<bool> C, vector<int> F, vector<int> T, vector<int> O, int time);

            void printTopologicalSorting(vector<int> O);

            void addArc(shared_ptr<Node> startNode, shared_ptr<Node> endNode, int weight);

            ~DirectedGraph();

            //ADD METHODS FOR A2 AND A3 HERE.

        private:
            int numberOfArcs;
            vector<shared_ptr<Connection>> arcs;
    };
}

#endif