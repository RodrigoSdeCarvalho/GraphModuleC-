#include <iostream>
#include <filesystem>
#include <string>
#include <cstdio>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <dirent.h>
#include <unistd.h>
#include <map>

#include "MainClass.h"
#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include "Node.h"
#include "Activities.h"

using namespace std;
using namespace filesystem;
using namespace GraphActivity;
using namespace GraphModule;

void Activities::A1Main(int question, string graphFile, bool defaultFlag)
{
    map<int, string> defaultGraphFileForQuestion = {
        {2, "fln_pequena.txt"},
        {3, "ContemCicloEuleriano.txt"},
        {4, "fln_pequena.txt"},
        {5, "fln_pequena.txt"}
    };

    if (defaultFlag)
    {
        graphFile = defaultGraphFileForQuestion[question];
    }

    runA1(question, graphFile);
}

void Activities::runA1(int question, string graphFile)
{
    cout << "A1 Question " << question << " on " << graphFile << endl;

    cout << endl;

    string graphFilePath = "A1/" + graphFile;
    unique_ptr<UndirectedGraph> graph = getUndirectedGraph(graphFilePath);

    if (question == 2)
    {
        int i;
        cout << "The graph has the vertices below:" << endl;
        graph->showNodes();
        cout << endl;
        cout << "Enter the start vertex: ";
        cin >> i;
        if (i < 1 || i > graph->getNumberOfVertices())
        {
            cout << "Invalid vertex" << endl;
            return;
        }
        cout << endl;
        cout << "Running BFS on vertex " << i << " in file " << graphFile << endl;
        i--;
        tuple<vector<int>, vector<int>> BFSTuple = graph->BFS(i);
        vector<int> D = get<0>(BFSTuple);
        vector<int> A = get<1>(BFSTuple);
        graph->printBFS(i, D, A);
    }
    else if (question == 3)
    {
        cout << "Eulerian Cycle " << "on file " << graphFile << endl;
        vector<int> cycle = graph->eulerianCycle(0); // Might be better to have a print function here as well
        graph->printEulerianCycle(cycle);
        cout << endl;
    }
    else if (question == 4)
    {
        int i;
        cout << "The graph has the vertices below:" << endl;
        graph->showNodes();
        cout << endl;
        cout << "Enter the start vertex: ";
        cin >> i;
        if (i < 1 || i > graph->getNumberOfVertices())
        {
            cout << "Invalid vertex" << endl;
            return;
        }
        cout << endl;
        cout << "Running Dijkstra on vertex " << i << " in file " << graphFile << endl;
        i--;
        tuple<vector<int>, vector<int>> dijkstraTuple = graph->dijkstra(i);
        vector<int> D = get<0>(dijkstraTuple);
        vector<int> A = get<1>(dijkstraTuple);
        graph->printDijkstra(i, D, A);
    }
    else if (question == 5)
    {
        cout << "Floyd Warshall" << " in file " << graphFile << endl;
        vector<vector<int>> D = graph->floydWarshall(); // Might be better to have a print function here as well
        graph->printFloydWarshall(D);
        cout << endl;
    }

    return;
}

void Activities::A2Main(int question, string graphFile, bool defaultFlag)
{
    //Implement A2.
}

void Activities::runA2(int question, string graphFile)
{
    //Implement A2.
}

void Activities::A3Main(int question, string graphFile, bool defaultFlag)
{
    //Implement A3.
}

void Activities::runA3(int question, string graphFile)
{
    //Implement A3.
}

unique_ptr<UndirectedGraph> Activities::getUndirectedGraph(string graphFilePath)
{
    path current_path = filesystem::current_path();
    string file_path = string(current_path.c_str()) + "/inputs/" + graphFilePath;
    UndirectedGraph* graph = new UndirectedGraph();
    buildUndirectedGraphFromInputFile(graph, file_path);

    unique_ptr<UndirectedGraph> graphUniquePtr(graph);

    return graphUniquePtr;
}

unique_ptr<DirectedGraph> Activities::getDirectedGraph(string graphFilePath)
{
    path current_path = filesystem::current_path();
    string file_path = string(current_path.c_str()) + "/inputs/" + graphFilePath;
    DirectedGraph* graph = new DirectedGraph();
    buildDirectedGraphFromInputFile(graph, file_path);

    unique_ptr<DirectedGraph> graphUniquePtr(graph);

    return graphUniquePtr;
}

void Activities::buildUndirectedGraphFromInputFile(UndirectedGraph* graph, string inputFilePath)
{
    char* inputFilePathChar = &inputFilePath[0];

    ifstream inputFile;
    inputFile.open(inputFilePathChar, ios::in);

    bool inputVertices = false;
    bool inputEdges = false;

    if (inputFile.is_open())
    {   
        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (ss >> token)
            {
                tokens.push_back(token);
            }

            if (tokens[0] == "*vertices")
            {
                inputVertices = true;
                continue;
            }

            if (tokens[0] == "*edges")
            {
                inputVertices = false;
                inputEdges = true;
                continue;
            }

            if (inputVertices)
            {
                int index = stoi(tokens[0]);
                string name;

                for (int i = 1; i < tokens.size() - 1; i++)
                {
                    name += tokens[i] + " ";
                }
                name += tokens[tokens.size() - 1];

                shared_ptr<Node> nodeSharedPtr = make_shared<Node>(index, name);
                graph->addNode(nodeSharedPtr);
            }

            if (inputEdges)
            {
                shared_ptr<Node> startNode = graph->getNodes()[stoi(tokens[0]) - 1];
                shared_ptr<Node> endNode = graph->getNodes()[stoi(tokens[1]) - 1];
                int weight = stoi(tokens[2]);

                graph->addEdge(startNode, endNode, weight);
            }
        }
    }
}

void Activities::buildDirectedGraphFromInputFile(DirectedGraph* graph, string inputFilePath)
{
    char* inputFilePathChar = &inputFilePath[0];

    ifstream inputFile;
    inputFile.open(inputFilePathChar, ios::in);

    bool inputVertices = false;
    bool inputArcs = false;

    if (inputFile.is_open())
    {   
        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (ss >> token)
            {
                tokens.push_back(token);
            }

            if (tokens[0] == "*vertices")
            {
                inputVertices = true;
                continue;
            }

            if (tokens[0] == "*arcs")
            {
                inputVertices = false;
                inputArcs = true;
                continue;
            }

            if (inputVertices)
            {
                int index = stoi(tokens[0]);
                string name;

                for (int i = 1; i < tokens.size() - 1; i++)
                {
                    name += tokens[i] + " ";
                }
                name += tokens[tokens.size() - 1];

                shared_ptr<Node> nodeSharedPtr = make_shared<Node>(index, name);
                graph->addNode(nodeSharedPtr);
            }

            if (inputArcs)
            {
                shared_ptr<Node> startNode = graph->getNodes()[stoi(tokens[0]) - 1];
                shared_ptr<Node> endNode = graph->getNodes()[stoi(tokens[1]) - 1];
                int weight = stoi(tokens[2]);

                graph->addArc(startNode, endNode, weight);
            }
        }
    }
}

string Activities::checkGraphKindFromInputFile(string graphFilePath)
{
    path current_path = filesystem::current_path();
    string file_path = string(current_path.c_str()) + "/inputs/" + graphFilePath;

    ifstream inputFile;
    inputFile.open(file_path, ios::in);

    if (inputFile.is_open())
    {
        
        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (ss >> token)
            {
                tokens.push_back(token);
            }

            if (tokens[0] == "*edges")
            {
                return "undirected";
            }

            if (tokens[0] == "*arcs")
            {
                return "directed";
            }
        }
    }
}
