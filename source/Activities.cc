#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <map>

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

void Activities::runA1(int question, const string& graphFile)
{
    cout << "A1 Question " << question << " on " << graphFile << endl;

    cout << endl;

    string graphFilePath = "A1/" + graphFile;

    checkGraphKindFromInputFile(graphFilePath, "undirected");
    
    auto graph = buildGraph<UndirectedGraph>(graphFilePath);

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
        graph->printBFS(D);
    }
    else if (question == 3)
    {
        cout << "Eulerian Cycle" << endl;
        vector<int> cycle = graph->eulerianCycle(0); 
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
}

void Activities::A2Main(int question, string graphFile, bool defaultFlag)
{
    map<int, string> defaultGraphFileForQuestion = {
        {1, "dirigido1.txt"},
        {2, "manha.txt"},
        {3, "arvore_geradora_min.txt"},
    };

    if (defaultFlag)
    {
        graphFile = defaultGraphFileForQuestion[question];
    }

    runA2(question, graphFile);
}

void Activities::runA2(int question, const string& graphFile)
{
    cout << "A2 Question " << question << " on " << graphFile << endl;

    cout << endl;

    string graphFilePath = "A2/" + graphFile;

    if (question == 1)
    {
        checkGraphKindFromInputFile(graphFilePath, "directed");
        auto directedGraph = buildGraph<DirectedGraph>(graphFilePath);
        cout << "Strongly Connected Components"<< endl;
        vector<int> transposedA = directedGraph->stronglyConnectedComponents();
        directedGraph->printStronglyConnectedComponents(transposedA);
        
    }

    else if (question == 2)
    {
        checkGraphKindFromInputFile(graphFilePath, "directed");
        auto directedGraph = buildGraph<DirectedGraph>(graphFilePath);
        cout << "Topological Sorting:" << endl;
        vector<shared_ptr<Node>> topologicalSorting = directedGraph->topologicalSorting();
        directedGraph->printTopologicalSorting(topologicalSorting);
    }

    else if (question == 3)
    {
        checkGraphKindFromInputFile(graphFilePath, "undirected");
        auto undirectedGraph = buildGraph<UndirectedGraph>(graphFilePath);
        int i;
        cout << "The graph has the vertices below:" << endl;
        undirectedGraph->showNodes();
        cout << endl;
        cout << "Enter the start vertex: ";
        cin >> i;
        if (i < 1 || i > undirectedGraph->getNumberOfVertices())
        {
            cout << "Invalid vertex" << endl;
            return;
        }
        cout << endl;
        cout << "Running Prim on vertex " << i << " in file " << graphFile << endl;
        i--;
        vector<int> A = undirectedGraph->prim(i);
        undirectedGraph->printPrim(A);
    }
}

void Activities::A3Main(int question, const string& graphFile, bool defaultFlag)
{
    //Implement A3.
}

void Activities::runA3(int question, const string& graphFile)
{
    //Implement A3.
}

void Activities::buildGraphFromInputFile(UndirectedGraph* graph, string inputFilePath)
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

void Activities::buildGraphFromInputFile(DirectedGraph* graph, string inputFilePath)
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
                float weight = stof(tokens[2]);

                graph->addArc(startNode, endNode, weight);
            }
        }
    }
}

void Activities::checkGraphKindFromInputFile(const string& graphFilePath, const string& expectedKind)
{
    path current_path = filesystem::current_path();
    string file_path = string(current_path.c_str()) + "/inputs/" + graphFilePath;

    ifstream inputFile;
    inputFile.open(file_path, ios::in);

    string foundKind;

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
                foundKind = "undirected";
            }

            if (tokens[0] == "*arcs")
            {
                foundKind = "directed";
            }
        }
    }

    if (foundKind != expectedKind)
    {
        throw invalid_argument("Graph needs to be " + expectedKind);
    }

}
