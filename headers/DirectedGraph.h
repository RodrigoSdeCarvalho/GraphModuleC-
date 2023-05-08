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

            vector<int> stronglyConnectedComponents();

            unique_ptr<DirectedGraph> buildTransposedGraph();
            
            tuple<vector<bool>,vector<int>,vector<int>,vector<int>> DFS();

            tuple<vector<bool>,vector<int>,vector<int>,vector<int>, int> DFSVisit(int vertice, vector<bool> C,vector<int> A,vector<int> T, vector<int> F, int time);

            vector<int> alteredDFS(vector<bool> C,vector<int> A,vector<int> T, vector<int> F);

            void printStronglyConnectedComponents(vector<int> A);

            vector<shared_ptr<Node>> topologicalSorting();

            tuple<vector<bool>, vector<int>, vector<int>, vector<shared_ptr<Node>>, int> DFSVisitTopologicalSorting(int v, vector<bool> C, vector<int> F, vector<int> T, vector<shared_ptr<Node>> O, int time);

            void printTopologicalSorting(vector<shared_ptr<Node>> O);

            void addArc(shared_ptr<Node> startNode, shared_ptr<Node> endNode, int weight);

            ~DirectedGraph();

            //ADD METHODS FOR A2 AND A3 HERE.

        private:
            int numberOfArcs;
            vector<shared_ptr<Connection>> arcs;
    };
}

#endif