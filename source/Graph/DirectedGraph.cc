#include <iostream>
#include <vector>
#include <string>
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

// A recursive function to print DFS starting from v
void DirectedGraph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v+1;
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
        {
            cout<<",";
            DFSUtil(*i, visited);
        }
    }
}
 
unique_ptr<DirectedGraph> DirectedGraph::getTranspose()
{    
    int V = this->numberOfVertices;
    auto transp_graph = new DirectedGraph();
    transp_graph->adj = new list<int>[V]; 

    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            transp_graph->adj[*i].push_back(v);
        }
    }
    unique_ptr<DirectedGraph> graphUniquePtr(transp_graph);
    return graphUniquePtr;
}

void DirectedGraph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if(!visited[*i])
        {
            fillOrder(*i, visited, Stack);
        }
    }
 
    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}
 
// The main function that finds and prints all strongly connected
// components
void DirectedGraph::stronglyConnectedComponents()
{
    int V = this->numberOfVertices;
    adj = new list<int>[V];

    for(auto conn:this->arcs){
        int i = conn->getStartNode()->getNumber() - 1;
        int j = conn->getEndNode()->getNumber() - 1 ;
        adj[i].push_back(j);
    }

    stack<int> Stack;
    
    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);
 
    // Create a reversed graph
    unique_ptr<DirectedGraph> transposedGraph = getTranspose();
 
    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();
 
        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            transposedGraph->DFSUtil(v, visited);
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

DirectedGraph::~DirectedGraph()
= default;
