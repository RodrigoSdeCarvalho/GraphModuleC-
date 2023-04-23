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

#include "MainClass.h"
#include "Graph.h"
#include "Node.h"

using namespace std;
using namespace filesystem;
using namespace GraphActivity;
using namespace GraphModule;

void MainClass::Main(int argc, char *argv[])
{
    bool argsAreOk = checkArguments(argc, argv);

    if (argsAreOk)
    {
        string Activity = argv[1];
        string graphFileOrFlag = argv[2];

        bool readAllFiles;
        if (graphFileOrFlag == "-ra")
        {
            readAllFiles = true;
        }
        else
        {
            readAllFiles = false;
        }

        if (readAllFiles)
        {
            vector<string> files = getInputFiles();
            for (vector<string>::iterator it = files.begin(); it != files.end(); ++it)
            {
                cout << "Running " << Activity << " on " << *it << endl;
                runActivity(Activity, *it);
            }
        }
        else
        {
            runActivity(Activity, graphFileOrFlag);
        }
    }
}

bool MainClass::checkArguments(int argc, char *argv[])
{
    if (argc != 3)
    {
        string errorMessage = "Error: Missing arguments \n"
                              "Usage: ./main <Activity> <<graphFile> or [-ra]> \n"
                              "Activity: A1, A2 or A3 \n"
                              "graphFile: name of the file \n"
                              "-ra: A flag that indicates if all files in inputs folder will be read";
        cout << errorMessage << endl;

        return false;
    }
    else
    {
        vector<string> validActivities = {"A1", "A2", "A3"};
        vector<string> validGraphFiles = getInputFiles();

        string activity = argv[1];
        string graphFileOrFlag = argv[2];

        bool activityIsValid = find_if(validActivities.begin(), validActivities.end(),[&](const std::string& file) { return file == activity; }) != validActivities.end();
        bool graphFileIsValid = find_if(validGraphFiles.begin(), validGraphFiles.end(),[&](const std::string& file) { return file == graphFileOrFlag; }) != validGraphFiles.end();
        bool flagIsValid = graphFileOrFlag == "-ra" ? true : false;

        if (activityIsValid && (graphFileIsValid || flagIsValid))
        {   
            return true;
        }
        else
        {
            string errorMessage = "Error: Invalid arguments \n"
                                  "Usage: ./main <Activity> <<graphFile> or [-ra]> \n"
                                  "Activity: A1, A2 or A3 \n"
                                  "graphFile: name of the file \n"
                                  "-ra: A flag that indicates if all files in inputs folder will be read";
            cout << errorMessage << endl;

            return false;
        }
    }
}

vector<string> MainClass::getInputFiles() {
    DIR* inputFolder;
    struct dirent* folderEntry;

    path current_path = filesystem::current_path();
    string folderPath = string(current_path.c_str()) + "/inputs";

    vector<string> inputs;
    if ((inputFolder = opendir(folderPath.c_str())) != nullptr) {
        while ((folderEntry = readdir(inputFolder)) != nullptr) {
            if (folderEntry->d_type == DT_REG) {
                inputs.push_back(string(folderEntry->d_name));
            }
        }
        closedir(inputFolder);
    }

    return inputs;
}

void MainClass::runActivity(string Activity, string graphFile)
{
    if (Activity == "A1")
    {
        A1Main(graphFile);
    }
    else if (Activity == "A2")
    {
        A2Main(graphFile);
    }
    else if (Activity == "A3")
    {
        A3Main(graphFile);
    }
}

void MainClass::A1Main(string graphFile)
{
    unique_ptr<Graph> graph = getGraph(graphFile);
    graph->BFS(0);
    // graph->eulerianCycle(0);
    // graph->dijkstra(0);
    // graph->flowdWarshall(0);
}

void MainClass::A2Main(string graphFile)
{
    //IMPLEMENT CODE TO ANSWER ALL A2 QUESTIONS.
}

void MainClass::A3Main(string graphFile)
{
    //IMPLEMENT CODE TO ANSWER ALL A3 QUESTIONS.
}

unique_ptr<Graph> MainClass::getGraph(string graphFile)
{
    path current_path = filesystem::current_path();
    string file_name = string(current_path.c_str()) + "/inputs/" + graphFile;
    Graph* graph = new Graph();
    buildGraphFromInputFile(graph, file_name);

    unique_ptr<Graph> graphUniquePtr(graph);

    return graphUniquePtr;
}

void MainClass::buildGraphFromInputFile(Graph* graph, string inputFilePath)
{
    char* inputFilePathChar = &inputFilePath[0];

    ifstream inputFile;
    inputFile.open(inputFilePathChar, ios::in);

    bool inputVertices = false;
    bool inputEdges = false;
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

            if (tokens[0] == "*edges")
            {
                inputVertices = false;
                inputEdges = true;
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

            if (inputEdges)
            {
                shared_ptr<Node> startNode = graph->getNodes()[stoi(tokens[0]) - 1];
                shared_ptr<Node> endNode = graph->getNodes()[stoi(tokens[1]) - 1];
                int weight = stoi(tokens[2]);

                graph->addEdge(startNode, endNode, weight);
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
