#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>
#include <memory>

#include "UndirectedGraph.h"
#include "AbstractGraph.h"
#include "Node.h"
#include "Connection.h"
#include "MinHeap.h"
#include "HeapNode.h"

using namespace std;
using namespace GraphModule;
#define INF numeric_limits<int>::max()

UndirectedGraph::UndirectedGraph()
{
    this->numberOfEdges = 0;
}

int UndirectedGraph::getDegreeOfNode(int nodeKey)
{
    shared_ptr<Node> node = this->nodes[nodeKey];
    return (node->getConnections()).size();
}

void UndirectedGraph::addEdge(shared_ptr<Node> node1, shared_ptr<Node> node2, int weight)
{
    weak_ptr<Node> node1WeakPtr(node1);
    weak_ptr<Node> node2WeakPtr(node2);

    shared_ptr<Connection> connection1SharedPtr = make_shared<Connection>(weight, node1WeakPtr, node2WeakPtr, true);
    shared_ptr<Connection> connection2SharedPtr = make_shared<Connection>(weight, node2WeakPtr, node1WeakPtr, true);
    
    this->edges.push_back(connection1SharedPtr);
    this->edges.push_back(connection2SharedPtr);

    weak_ptr<Connection> connection1WeakPtr(connection1SharedPtr);
    node1->addConnection(connection1SharedPtr);

    weak_ptr<Connection> connection2WeakPtr(connection2SharedPtr);
    node2->addConnection(connection2SharedPtr);

    this->numberOfEdges++;
}

tuple<vector<int>, vector<int>> UndirectedGraph::BFS(int startNodeIndex)
{
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<shared_ptr<Node>> nodes = this->nodes;
    vector<bool> V; // Vector of visited nodes.
    vector<int> D; // Vector of distances from the start node.
    vector<int> A; // Vector of parent nodes.
    vector<vector<int>> levels; // Vector of vectors to store vertices found at each level
    for (int i = 0; i <= numberOfVertices; i++)
    {
        V.push_back(false); // Initialize with false.
        D.push_back(1000000); // Initialize with infinity.
        A.push_back(-1); // Initialize with -1.
    }
    V[startNodeIndex] = true; // Mark the start node as visited.
    D[startNodeIndex] = 0; // Set the distance from the start node to itself to 0.
    A[startNodeIndex] = -1; // Set the parent of the start node to -1.

    queue<int> Q; // Create a queue.
    Q.push(startNodeIndex); // Push the start node to the queue.
    levels.push_back(vector<int>({startNodeIndex})); // Add the start node to level 0
    while (!Q.empty())
    {
        int u = Q.front(); // Get the first element in the queue.
        Q.pop(); // Remove the first element in the queue.
        vector<shared_ptr<Connection>> connections = nodes[u]->getConnections(); // Get the connections of the start node.

        for (int i = 0; i != connections.size(); ++i)
        {
            shared_ptr<Connection> conn = connections[i];
            shared_ptr<Node> vNode = (conn)->getEndNode(); // Get the end node of the connection.
            int v = vNode->getNumber() - 1; // Get the index of the end node of the connection.
            if (!V[v])
            { // If the end node of the connection is not visited.
                V[v] = true; // Mark the end node as visited.
                D[v] = D[u] + 1; // Set the distance from the start node to the end node to the distance from the start node to the start node of the connection plus 1.
                A[v] = u; // Set the parent of the end node to the start node of the connection.
                Q.push(v); // Push the end node to the queue.
            }
        }
    }

    return make_tuple(D, A);
}

void UndirectedGraph::printBFS(int startNodeIndex, vector<int> D, vector<int> A)
{
    // Print the levels and vertices found in each level.
    for (int level = 0; level <= numberOfVertices; level++) {
        bool foundVertices = false;
        for (int i = 0; i < numberOfVertices; i++) {
            if (D[i] == level) {
                if (!foundVertices) {
                    cout << level << ":";
                    foundVertices = true;
                }
                cout << " " << nodes[i]->getName();
            }
        }
        if (!foundVertices) {
            break; // No more vertices to print.
        }
        cout << endl;
    }
}

void UndirectedGraph::eulerianCycle(int startNodeIndex)
{
    // primeira linha dever ́a conter o n ́umero 0 caso o grafo n ̃ao contenha o ciclo euleriano. Caso contenha, dever ́a ser impresso 1 na primeira linha e em seguida, a sequˆencia de v ́ertices que corresponde ao ciclo dever ́a ser impressa.
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<vector<int>> C;
    int numberOfConnectionsBeginNode = this->getDegreeOfNode(startNodeIndex);
    int beginNodeIndex = startNodeIndex;
    if (numberOfConnectionsBeginNode == 0) // If the initial node is not connected we don't have a cycle, it needs to be on the same connected component
    { 
        cout << "0" << endl;
        return;
    }

    for (int i = 0; i <= numberOfVertices; i++) // Initialize with false the connections, if there isn't, initialize with infinity.
    {
        vector<int> connections;
        for (int j = 0; j <= numberOfVertices; j++)
        {
            if (this->nodes[i]->IsConnectedWith(this->nodes[j]))
            {
                connections.push_back(false); 
            }
            else 
            {
                connections.push_back(INF);
            }
        }
        C.push_back(connections); 
    }
    
    tuple<bool, vector<int>> returnedValues = searchEulerianSubcycle(beginNodeIndex, C); // Searches for subcycles
    bool r = get<0>(returnedValues);
    vector<int> cycle = get<1>(returnedValues);

    if(!r) // There is no cycle
    { 
        cout << "0" << endl;
        return;
    }
    else
    {
        bool allVisited = true; 
        for (auto line : C) // Searches for a false value in C, if there is at least one, all visited is false. 
        {
  	        for (auto element : line)
            {
                allVisited &= element;
            }
        }
        if(!allVisited)
        { // There is a node that wasn't visited, so there is no cycle since there is one that is unconnected
            cout << "0" << endl;
            return;
        }
        else
        {
            cout << "1" << endl;
            for(int i=0; i <= cycle.size(); i++)
            {
                cout << cycle[i] << " ";
            }
            cout << endl;
        }
    }
    return;
}

tuple<bool, vector<int>> UndirectedGraph::searchEulerianSubcycle(int beginNodeIndex, vector<vector<int>> C)
{
    vector<int> cycle;
    int v = beginNodeIndex;
    cycle.push_back(v);
    int t = v;

    do
    {
        int u = -1;
        auto neighbours = this->nodes[v]->getNeighbours();
        for (auto neighbour : neighbours)
        {
            int neighbourIndex = neighbour->getNumber();
            if (!C[neighbourIndex][v]) { // Selects an edge that C=false
                u = neighbourIndex;
                break;
            }
        }
        if (u == -1) { // If u = -1 it means that there are no C=false
            return make_tuple(false, vector<int>({0}));
        } else {
            C[u][v] = true;
            C[v][u] = true;
            v = u;
            cycle.push_back(v); // Adds v to the end of the cycle.
        }
    }while (t != beginNodeIndex);

    for(auto i = cycle.begin(); i != cycle.end(); i++) // Checks for subcycles
    {
        int node = *i;
        auto neighbours = this->nodes[node]->getNeighbours();
        
        for (auto neighbour : neighbours) 
        {
            int neighbourIndex = neighbour->getNumber();
            if (!C[neighbourIndex][node]) 
            {
                tuple<bool, vector<int>> returnedValues = searchEulerianSubcycle(node, C);
                bool r = get<0>(returnedValues);
                vector<int> subcycle = get<1>(returnedValues);

                if (r) 
                {
                    for(auto j = (subcycle.begin())++; j != subcycle.end(); j++)
                    {
                        i = cycle.insert(i, *j);
                    }
                }
            }
        }
    }

    return make_tuple(true, cycle);
}
 
tuple<vector<int>, vector<int>> UndirectedGraph::dijkstra(int startNodeIndex)
{
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<shared_ptr<Node>> nodes = this->nodes; // Vector of nodes in the graph.
    vector<int> D = vector<int>(numberOfVertices); // Vector of distances from the start node.
    vector<int> A = vector<int>(numberOfVertices); // Vector of parent nodes.
    vector<bool> C(numberOfVertices, false); // Vector of visited nodes.
    int visitedNodes = 0; // Counter for the number of visited nodes.

    for (int i = 0; i < numberOfVertices; i++)
    {
        D[i] = 1000000; // Initialize with infinity.
        A[i] = -1; // Initialize with -1.
    }

    D[startNodeIndex] = 0; // Set the distance from the start node to itself to 0.
    
    A[startNodeIndex] = -1; // Set the parent of the start node to -1.

    MinHeap minHeap = MinHeap(); // Create a min heap. 
    for (int n = 0; n < numberOfVertices; n++)
    {
        minHeap.insert(this->nodes[n], D[n]);
    }

    while (visitedNodes < numberOfVertices)
    {
        shared_ptr<Node> u = minHeap.popMin();
        C[u->getNumber() - 1] = true;
        visitedNodes++;
        vector<shared_ptr<Connection>> uConnections = u->getConnections();
        for (int i =0; i < uConnections.size(); i++)
        {
            int otherNodeNumber = uConnections[i]->getEndNode()->getNumber();
            if (C[otherNodeNumber - 1] == false)
            {
                shared_ptr<Node> v = uConnections[i]->getEndNode();
                int w = uConnections[i]->getWeight();
                if (D[v->getNumber() - 1] > D[u->getNumber() - 1] + w) 
                {
                    D[v->getNumber() - 1] = D[u->getNumber() - 1] + w;
                    A[v->getNumber() - 1] = u->getNumber() - 1;
                    minHeap.updatePriority(v, D[v->getNumber() - 1]);
                }
            }
        }

    }

    return make_tuple(D, A);
}

void UndirectedGraph::printDijkstra(int startNodeIndex, vector<int> D, vector<int> A)
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        vector<int> path;
        int currentNodeIndex = i;
        while (currentNodeIndex != startNodeIndex)
        {
            path.insert(path.begin(), currentNodeIndex + 1);
            currentNodeIndex = A[currentNodeIndex];
        }
        path.insert(path.begin(), startNodeIndex + 1);

        if (i == startNodeIndex)
        {
            cout << path.back() << ": ";
        }
        else
        {
            cout << path.back() << ": " << startNodeIndex + 1 << ",";
        }

        for (int j = 1; j < path.size() - 1; j++)
        {
            cout << path[j] << ",";
        }
        cout << path[path.size() - 1] << "; d = " << D[i] << endl;
    }
}

void UndirectedGraph::floydWarshall(int startNodeIndex)
{
	vector<vector<float>> D;
    int numberOfVertices = this->numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++) //Populating the Matrix D
    {
        vector<float> connections;
		for (int j = 0; j < numberOfVertices; j++) //verify if it is not actually just <= for all the other cases
        {
            if (this->nodes[i+1]->IsConnectedWith(this->nodes[j+1]))
            {
                float weight = this->nodes[i+1]->getConnectionWith(this->nodes[j+1])->getWeight();
                connections.push_back(weight); 
            }
            else 
            {
                if (i==j)
                {
                    connections.push_back(0);
                }
                else
                {
                    connections.push_back(INF);
                }
            }
		}
        D.push_back(connections); // should print this to verify correctness
	}

	for (int k = 0; k < numberOfVertices; k++) // finds minimum
    {
		for (int u = 0; u < numberOfVertices; u++) 
        { 
			for (int v = u; v < numberOfVertices; v++) 
            {
				float min_weight = min(D[u][v], (D[u][k] + D[k][v]));
				D[u][v] = min_weight;
				D[v][u] = min_weight;
			}
		}
	}

	for (int i = 0; i < numberOfVertices; i++) 
    {
		cout << (i+1) << ": ";
		for (int j = 0; j < numberOfVertices-1; j++) 
        {
			cout << D[i][j] << ",";
		}
		cout << D[i][numberOfVertices-1] << endl;
	}

    return;
}

UndirectedGraph::~UndirectedGraph()
{

}
