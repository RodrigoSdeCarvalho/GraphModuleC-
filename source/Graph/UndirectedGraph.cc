#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <memory>

#include "Graph/UndirectedGraph.h"
#include "Graph/Node.h"
#include "Graph/Connection.h"
#include "Graph/MinHeap.h"
#include "Graph/HeapNode.h"

using namespace std;
using namespace GraphModule;

UndirectedGraph::UndirectedGraph()
{
    this->numberOfEdges = 0;
}

int UndirectedGraph::getDegreeOfNode(int nodeKey)
{
    shared_ptr<Node> node = this->nodes[nodeKey];
    vector<shared_ptr<Connection>> connections = node->getConnections();

    int degree = connections.size();

    
    for (const auto& nodeToCheck : this->nodes)
    {
        vector<shared_ptr<Connection>> connectionsToCheck = nodeToCheck->getConnections();

        for (const auto& connectionToCheck : connectionsToCheck)
        {
            shared_ptr<Node> nodeConnectedTo = connectionToCheck->getEndNode();

            if (nodeConnectedTo->getNumber() == node->getNumber())
            {
                degree++;
            }
        }
    }

    return degree;
}

void UndirectedGraph::addEdge(const shared_ptr<Node>& node1, const shared_ptr<Node>& node2, int weight)
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

        for (const auto& conn : connections)
        {
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

void UndirectedGraph::printBFS(vector<int> D)
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
                cout << " " << nodes[i]->getNumber();
            }
        }
        if (!foundVertices) {
            break; // No more vertices to print.
        }
        cout << endl;
    }
}

vector<int> UndirectedGraph::eulerianCycle(int startNodeIndex)
{
    int numberOfVertices = this->numberOfVertices; // Number of vertices in the graph.
    vector<vector<int>> C;
    int numberOfConnectionsBeginNode = this->getDegreeOfNode(startNodeIndex)/2;
    int beginNodeIndex = startNodeIndex;
    if (numberOfConnectionsBeginNode == 0) // If the initial node is not connected we don't have a cycle, it needs to be on the same connected component
    { 
        return vector<int>({0});
    }

    for (int i = 0; i < numberOfVertices; i++){
        if(this->nodes[i]->getConnections().size()%2 != 0) //If there is a node that has an odd degree we don't have a cycle
        {
            return vector<int>({0});
        }
    }

    for (int i = 0; i < numberOfVertices; i++) // Initialize with false the connections, if there isn't, initialize with infinity.
    {
        vector<int> connections;
        for (int j = 0; j < numberOfVertices; j++)
        {
            tuple<bool, shared_ptr<Connection>> returnedValues = this->nodes[i]->getConnectionWith(this->nodes[j]);
            if (get<0>(returnedValues))
            {
                connections.push_back(false); 
            }
            else 
            {
                connections.push_back(1000000);
            }
        }
        C.push_back(connections); 
    }

    tuple<bool, vector<int>, vector<vector<int>>> returnedValues = searchEulerianSubcycle(beginNodeIndex, C); // Searches for subcycles

    bool r = get<0>(returnedValues);
    vector<int> cycle = get<1>(returnedValues);
    vector<vector<int>> new_C = get<2>(returnedValues);
    
    if(!r) // There is no cycle
    { 
        return vector<int>({0});
    }
    else
    {
        bool allVisited = true; 
        for (const auto& line : new_C) // Searches for a false value in C, if there is at least one, all visited is false.
        {
  	        for (auto element : line)
            {
                allVisited = allVisited && element;
            }
        }
        if(!allVisited)
        { // There is a node that wasn't visited, so there is no cycle since there is one that is unconnected
            return vector<int>({0});
        }
        else
        {
            cout << "1" << endl;
            return cycle;
        }
    }
}

tuple<bool, vector<int>, vector<vector<int>>> UndirectedGraph::searchEulerianSubcycle(int beginNodeIndex, vector<vector<int>> C)
{
    vector<int> cycle;
    int v = beginNodeIndex;
    vector<vector<int>> adjMatrix = std::move(C);
    cycle.push_back(v);
    int t = v;

    do
    {
        int u = -1;
        auto neighbours = this->nodes[v]->getNeighbours();
        for (const auto& neighbour : neighbours)
        {
            int neighbourIndex = neighbour->getNumber() - 1;
            if (!adjMatrix[neighbourIndex][v]) { // Selects an edge that C=false
                u = neighbourIndex;
                break;
            }
        }
        if (u == -1) { // If u = -1 it means that there are no C=false
            return make_tuple(false, vector<int>({0}), adjMatrix);
        } else {
            adjMatrix[u][v] = true;
            adjMatrix[v][u] = true;
            v = u;
            cycle.push_back(v); // Adds v to the end of the cycle.
        }
    }while (t != v);

    for(auto i = cycle.begin(); i != cycle.end(); i++) // Checks for subcycles
    {
        int node = *i;
        auto neighbours = this->nodes[node]->getNeighbours();
        
        for (const auto& neighbour : neighbours)
        {
            int neighbourIndex = neighbour->getNumber() - 1;
            if (!adjMatrix[neighbourIndex][node]) 
            {
                tuple<bool, vector<int>, vector<vector<int>>> returnedValues = searchEulerianSubcycle(node, adjMatrix);
                adjMatrix = get<2>(returnedValues);
                bool r = get<0>(returnedValues);
                vector<int> subcycle = get<1>(returnedValues);

                if (r) 
                {
                    for(auto j = ++(subcycle.begin()); j != subcycle.end(); j++)
                    {
                        i = cycle.insert(i, *j);
                    }
                }
            }
        }
    }

    return make_tuple(true, cycle, adjMatrix);
}

void UndirectedGraph::printEulerianCycle(vector<int> cycle)
{

    for(int i=0; i < cycle.size(); i++)
    {
        if (cycle.size()==1)
        {
            cout << cycle[i] << " ";
        }
        else
        {  
            cout << cycle[i] + 1 << " "; //+1 to print accordingly to the input
        }
    }
    cout << endl;
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
        for (auto & uConnection : uConnections)
        {
            int otherNodeNumber = uConnection->getEndNode()->getNumber();
            if (!C[otherNodeNumber - 1])
            {
                shared_ptr<Node> v = uConnection->getEndNode();
                int w = uConnection->getWeight();
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
        cout << path[path.size() - 1] << "; d=" << D[i] << endl;
    }
}

vector<vector<int>> UndirectedGraph::floydWarshall()
{
	vector<vector<int>> D;
    int numberOfVertices = this->numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++) //Populating the Matrix D
    {
        vector<int> connections;
		for (int j = 0; j < numberOfVertices; j++) //verify if it is not actually just <= for all the other cases
        {
            tuple<bool,shared_ptr<Connection>> returnedValues = this->nodes[i]->getConnectionWith(this->nodes[j]);
            if (get<0>(returnedValues))
            {
                int weight = get<1>(returnedValues)->getWeight();
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
                    connections.push_back(1000000);
                }
            }
		}
        D.push_back(connections); // should print this to verify correctness
	}

    for (int k = 0; k < numberOfVertices; k++) 
    {
        for (int i = 0; i < numberOfVertices; i++) 
        {
            for (int j = 0; j < numberOfVertices; j++) 
            {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }

    return D;
}

void UndirectedGraph::printFloydWarshall(vector<vector<int>> D)
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < numberOfVertices; j++)
        {
            if (D[i][j] == 1000000)
            {
                cout << "inf" << " ";
            }
            else
            {
                cout << D[i][j] << " ";
            }
        }
        cout << endl;
    }
}

vector<vector<int>> UndirectedGraph::kruskal()
{

}

void UndirectedGraph::printKruskal(const vector<vector<int>>& A)
{

}

vector<int> UndirectedGraph::prim(int startNodeIndex)
{
    int r = startNodeIndex;

    vector<float> K;

    vector<int> A;

    for (int i = 0; i < this->numberOfVertices; ++i)
    {
        K.push_back(1000000);
        A.push_back(-1);
    }

    K[r] = 0;

    unordered_map<int, float> Q;
	for (int i = 1; i < this->numberOfVertices; ++i)
    {
		Q.emplace(i, K[i]);
    }
    while (!Q.empty())
    {
		auto min = Q.begin();
		for (auto j = Q.begin(); j != Q.end(); ++j)
        { //finds argmin
			if ((*min).second > (*j).second)
            {
				min = j;
            }
		}

		int u = (*min).first;
		Q.erase(min);

		vector<shared_ptr<Node>> neighbours = this->nodes[u]->getNeighbours();
		for (const shared_ptr<Node>& neighbour : neighbours)
        {
            tuple<bool,shared_ptr<Connection>> returnedValues = this->nodes[u]->getConnectionWith(neighbour);
			int v = neighbour->getNumber(); // neighbour's Index
            shared_ptr<Connection> connectionWithV = get<1>(returnedValues);
            float weight = connectionWithV->getWeight();
			if (Q.find(v) != Q.end() && weight < K[v])
            {
				A[v] = u;
				K[v] = weight;
				Q[v] = K[v];
			}
		}
	}

    return A;
}

void UndirectedGraph::printPrim(vector<int> A)
{
    cout << "Prim:" << endl;
    float weightSum = 0;
    string message;
    for (int i = 2; i < this->numberOfVertices; ++i)
    {
        int nodeIndex = A[i];
        if (nodeIndex >= 0 && nodeIndex < this->numberOfVertices)
        {
            if (!message.empty())
            {
                message += ", ";
            }
            message += to_string(i) + "-" + to_string(nodeIndex);
            auto nodeOnTheOtherEnd = get<1>(this->nodes[i]->getConnectionWith(this->nodes[nodeIndex]));
            weightSum += nodeOnTheOtherEnd->getWeight();
        }
    }

    cout << weightSum << endl;
    cout << message << endl;
}

UndirectedGraph::~UndirectedGraph()
= default;
