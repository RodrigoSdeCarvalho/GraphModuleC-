#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <memory>

#include "DirectedGraph.h"
#include "Node.h"
#include "Connection.h"

using namespace std;
using namespace GraphModule;

DirectedGraph::DirectedGraph()
{
    this->numberOfArcs = 0;
}

int DirectedGraph::getDegreeOfNode(int nodeKey)
{
    shared_ptr<Node> node = this->nodes[nodeKey];

    return (node->getIncomingConnections()).size() + (node->getOutgoingConnections()).size();
}

int DirectedGraph::getInDegreeOfNode(int nodeKey)
{
    shared_ptr<Node> node = this->nodes[nodeKey];

    return (node->getIncomingConnections()).size();
}

int DirectedGraph::getOutDegreeOfNode(int nodeKey)
{
    shared_ptr<Node> node = this->nodes[nodeKey];

    return (node->getOutgoingConnections()).size();
}

vector<int> DirectedGraph::stronglyConnectedComponents()
{
    tuple<vector<bool>,vector<int>,vector<int>,vector<int>> DFSVectors = this->DFS();

    vector<bool> C = get<0>(DFSVectors);
    vector<int> T = get<1>(DFSVectors);
    vector<int> A = get<2>(DFSVectors);
    vector<int> F = get<3>(DFSVectors);

    unique_ptr<DirectedGraph> transposedGraph = buildTransposedGraph();

    vector<int> transposedA = transposedGraph->alteredDFS(C, A, T, F);

    return transposedA;
}

unique_ptr<DirectedGraph> DirectedGraph::buildTransposedGraph()
{
    auto graph = new DirectedGraph();

    //builds graph with transposed A
    for (int index = 0; index < this->numberOfVertices; index++)
    {   //adds nodes
        shared_ptr<Node> nodeSharedPtr = make_shared<Node>(this->nodes[index]->getNumber(), this->nodes[index]->getName());
        graph->addNode(nodeSharedPtr);
    }
    for (int index = 0; index < this->numberOfArcs; index++)
    {   //adds arcs
        shared_ptr<Node> startNode = this->arcs[index]->getEndNode();
        shared_ptr<Node> endNode = this->arcs[index]->getStartNode();
        float weight = this->arcs[index]->getWeight();
        graph->addArc(startNode, endNode, weight);
    }

    unique_ptr<DirectedGraph> graphUniquePtr(graph);

    return graphUniquePtr;
}

tuple<vector<bool>,vector<int>,vector<int>,vector<int>> DirectedGraph::DFS()
{
    vector<bool> C;
    vector<int> T;
    vector<int> A;
    vector<int> F;
    int time = 0;

    for (int i = 0; i < this->numberOfVertices; ++i) 
    { // initializes values
        C.push_back(false);
        T.push_back(1000000);
        A.push_back(-1);
        F.push_back(1000000);
	}

	for (int vertex = 0; vertex < this->numberOfVertices; ++vertex)
    {
		if (!C[vertex])
        { // if there is a vertex not visited
			tuple<vector<bool>,vector<int>,vector<int>,vector<int>, int> DFSVisitValues = this->DFSVisit(vertex, C, A, T, F, time);
            C = get<0>(DFSVisitValues);
            T = get<1>(DFSVisitValues);
            A = get<2>(DFSVisitValues);
            F = get<3>(DFSVisitValues);
            time = get<4>(DFSVisitValues);
        }
	}

    return make_tuple(C, T, A, F);
}

tuple<vector<bool>,vector<int>,vector<int>,vector<int>, int> DirectedGraph::DFSVisit(int vertex, vector<bool> C,vector<int> A,vector<int> T, vector<int> F, int time)
{
    C[vertex] = true;
	time++;
	T[vertex] = time;

	vector<shared_ptr<Node>> outgoingNeighbours = this->nodes[vertex]->getOutgoingNeighbours();

    for (const shared_ptr<Node>& neighbor : outgoingNeighbours)
    {
        int neighborVertice = neighbor->getNumber() - 1;
		if (!C[neighborVertice]) {
            A[neighborVertice] = vertex;
			tuple<vector<bool>,vector<int>,vector<int>,vector<int>, int> DFSVisitValues = this->DFSVisit(neighborVertice, C, A, T, F, time);
            C = get<0>(DFSVisitValues);
            T = get<1>(DFSVisitValues);
            A = get<2>(DFSVisitValues);
            F = get<3>(DFSVisitValues);
            time = get<4>(DFSVisitValues);
        }
	}

	time++;
	F[vertex] = time;
    return make_tuple(C, T, A, F, time);
}

vector<int> DirectedGraph::alteredDFS(vector<bool> C,vector<int> A,vector<int> T, vector<int> F)
{
    int time = 0;
    for (int i = 0; i < this->numberOfVertices; ++i)
    {
        C.push_back(false);
        T.push_back(1000000);
        A.push_back(-1);
        F.push_back(1000000);
	}
	
	bool temp = true;
	while (temp)
    { //T in decrescent order
		temp = false;
		int max = -1;
		int maxVertice = -1;
		for (int i = 0; i < this->numberOfVertices; ++i)
        {
			if (F[i] > max && !C[i])
            {
				temp = true;
				max = F[i];
				maxVertice = i;
			}
		}
		if (maxVertice != -1)
        {
			DFSVisit(maxVertice, C, A, T, F, time);
		}
	}
    return A;
}

void DirectedGraph::printStronglyConnectedComponents(vector<int> A)
{
    bool firstComponent = true;
    for (int i = 0; i < this->numberOfVertices; i++) {
        if (A[i] == -1) {
            if (!firstComponent) {
                cout << "\n";
            }
            cout << i + 1;
            firstComponent = false;
        } else {
            cout << ", " << i + 1;
        }
    }
    cout << "\n";
}

vector<shared_ptr<Node>> DirectedGraph::topologicalSorting()
{
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<shared_ptr<Node>> nodes = this->nodes; // Vector of nodes in the graph.
    vector<bool> C; // Vector of 
    vector<int> T; // Vector of 
    vector<int> F; // Vector of
    vector<shared_ptr<Node>> O; // Vector of nodes in topological order.
    int time = 0; // Time variable.

    // Initializes values.
    for (int i = 0; i < numberOfVertices; ++i)
    {
        C.push_back(false);
        T.push_back(100000);
        F.push_back(100000);
    }

    for (int u = 0; u < numberOfVertices; ++u)
    {
        if (!C[u])
        {   
            this->DFSVisitTopologicalSorting(u, C, F, T, O, time);
        }
    }

    return O;
}

void DirectedGraph::DFSVisitTopologicalSorting(int v, vector<bool> &C, vector<int> &F, vector<int> &T, vector<shared_ptr<Node>> &O, int &time)
{
    C[v] = true;
    time++;
    T[v] = time;

    vector<shared_ptr<Node>> outgoingNeighbours = this->nodes[v]->getOutgoingNeighbours();
    for (const auto& neighbour : outgoingNeighbours)
    {
        int neighbourVertice = neighbour->getNumber();
        if (!C[neighbourVertice - 1])
        {
            this->DFSVisitTopologicalSorting(neighbourVertice -1, C, F, T, O, time);
        }
    }

    time++;
    F[v] = time;

    O.insert(O.begin(), nodes[v]);
}

void DirectedGraph::printTopologicalSorting(const vector<shared_ptr<Node>> &O)
{
    for (auto & i : O)
    {
        cout << i->getName() << " -> ";
    }
}

void DirectedGraph::addArc(const shared_ptr<Node> &startNode, const shared_ptr<Node> &endNode, float weight)
{
    weak_ptr<Node> startNodeWeakPtr(startNode);
    weak_ptr<Node> endNodeWeakPtr(endNode);

    shared_ptr<Connection> connectionSharedPtr = make_shared<Connection>(weight, startNodeWeakPtr, endNodeWeakPtr, false);
    this->arcs.push_back(connectionSharedPtr);
    
    weak_ptr<Connection> connectionWeakPtr(connectionSharedPtr);
    startNode->addOutgoingConnection(connectionWeakPtr);
    endNode->addIncomingConnection(connectionWeakPtr);

    this->numberOfArcs++;
}

DirectedGraph::~DirectedGraph()
= default;
