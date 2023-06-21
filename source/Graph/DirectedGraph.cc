#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <memory>

#include "Graph/DirectedGraph.h"
#include "Graph/Node.h"
#include "Graph/Connection.h"

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

void DirectedGraph::DFSVisit(int v, bool C[])
{
    C[v] = true;
    cout << v+1; // Prints current v node
 
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    { // iters for the connections
        if (!C[*i])
        {
            cout<<",";
            DFSVisit(*i, C);
        }
    }
}
 
unique_ptr<DirectedGraph> DirectedGraph::BuildTransposedGraph()
{    
    int V = this->numberOfVertices;
    auto transp_graph = new DirectedGraph();
    transp_graph->adj = new list<int>[V]; 

    for (int v = 0; v < V; v++)
    {
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        { // Inverts connections of arcs
            transp_graph->adj[*i].push_back(v);
        }
    }
    unique_ptr<DirectedGraph> graphUniquePtr(transp_graph);
    return graphUniquePtr;
}

void DirectedGraph::DFS(int v, bool C[], stack<int> &Stack)
{
    C[v] = true;
 
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if(!C[*i])
        {
            DFS(*i, C, Stack);
        }
    }
 
    Stack.push(v); // Adds to stack once all have been visited in regards to v node
}
 
void DirectedGraph::stronglyConnectedComponents()
{
    int V = this->numberOfVertices;
    adj = new list<int>[V];

    for(auto conn:this->arcs)
    { // Builds adjacency matrix
        int i = conn->getStartNode()->getNumber() - 1;
        int j = conn->getEndNode()->getNumber() - 1 ;
        adj[i].push_back(j);
    }

    stack<int> Stack;

    bool *C = new bool[V];
    for(int i = 0; i < V; i++)
    { // Initializes values of C to keep track of visited nodes during DFS
        C[i] = false;
    }
 
    for(int i = 0; i < V; i++)
    { // Puts in stack according to their finishing times
        if(C[i] == false)
        {
            DFS(i, C, Stack);
        }
    }
 
    unique_ptr<DirectedGraph> transposedGraph = BuildTransposedGraph();
 
    for(int i = 0; i < V; i++)
    { // Reset values for the second DFS
        C[i] = false;
    }
 
    while (Stack.empty() == false)
    {
        int v = Stack.top();
        Stack.pop();
        if (C[v] == false)
        {
            transposedGraph->DFSVisit(v, C);
            cout << endl;
        }
    }
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
        if (i == O.back())
        {
            cout << i->getName() << ".\n";
        }
        else
        {
            cout << i->getName() << " -> ";
        }
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

int DirectedGraph::edmondsKarp(int beginNodeIndex, int endNodeIndex)
{
    /* Crie um programa que receba um grafo dirigido e ponderado como argumento. Ao final, imprima na tela:
    /  - [X] o valor do fluxo maximo resultante da execucao do algoritmo de Edmonds-Karp.*/

    int V = this->numberOfVertices; // Number of vertices in the graph.
    vector<vector<float>> graphAdjacency; // Adjacency matrix
    int parent[V]; // BFS result array
    int u, v;
    int max_flow = 0;

    for (u = 0; u < V; u++) 
    { // Builds adjacency matrices. Initialize with wieghts, if there isn't, initialize with 0.
        vector<float> connections;
        for (int v = 0; v < V; v++)
        {    
            connections.push_back(0);
        }
        graphAdjacency.push_back(connections);
    } 
    for (u = 0; u < V; u++) 
    { // this is so bad it makes me wanna puke
        vector<shared_ptr<Connection>> cons = this->nodes[u]->getOutgoingConnections();
        for (auto m : cons) 
        {
            graphAdjacency[m->getStartNode()->getNumber()-1][m->getEndNode()->getNumber()-1] = m->getWeight();
        }
    }
    this->residualNetwork = graphAdjacency;
    
    while (BFS(beginNodeIndex, endNodeIndex, parent)) 
    {
        float path_flow = 1000000;
        for (v = endNodeIndex; v != beginNodeIndex; v = parent[v]) 
        {
            u = parent[v];
            path_flow = min(path_flow, this->residualNetwork[u][v]);
        }
 
        for (v = endNodeIndex; v != beginNodeIndex; v = parent[v]) 
        { // Updates and changes arcs
            u = parent[v];
            this->residualNetwork[u][v] -= path_flow;
            this->residualNetwork[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int DirectedGraph::BFS(int beginNodeIndex, int endNodeIndex, int parent[])
{
    int V = this->numberOfVertices;
    bool visited[V];
    queue<int> Q;

    memset(visited, 0, sizeof(visited)); //Initialize as false
    Q.push(beginNodeIndex);
    visited[beginNodeIndex] = true;
    parent[beginNodeIndex] = -1;
    
    while (!Q.empty()) 
    {
        int u = Q.front();
        Q.pop();
        for (int v = 0; v < V; v++) 
        {
            if (visited[v] == false && this->residualNetwork[u][v] > 0) 
            {
                if (v == endNodeIndex) 
                {
                    parent[v] = u;
                    return 1;
                }
                Q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }

    }
    return 0;
}

void DirectedGraph::printEdmontsKarp(int max_flow)
{
    cout << "\nMax flow equals "<< max_flow <<endl;
}

DirectedGraph::~DirectedGraph()
= default;
