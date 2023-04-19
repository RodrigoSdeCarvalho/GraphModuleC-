#include <iostream>
#include <filesystem>
#include <string>
#include <cstdio>

#include "MainClass.h"
#include "Graph.h"
#include "Node.h"

using namespace std;
using namespace filesystem;
using namespace GraphModule;

void MainClass::A1Main()
{
    path current_path = filesystem::current_path();
    string file_name = string(current_path.c_str()) + "/inputs/fln_pequena.txt";
    Graph graph = Graph(file_name);

    // for (int i = 0; i < graph.getNumberOfVertices(); i++)
    // {
    //     cout << "Node: " << graph.getNodes()[i] << endl;
    //     for (int j = 0; j < graph.getNodes()[i]->getConnections().size(); j++)
    //     {
    //         cout << "Connection: " << graph.getNodes()[i]->getConnections()[j] << endl;
    //     }
    // }

    for (int i = 0; i < graph.getNumberOfVertices(); i++)
    {  
        cout << "CALLING DIJKSTRA FOR NODE " << i << endl;
         graph.dijkstra(i);
    }
}

void MainClass::A2Main()
{
    //IMPLEMENT CODE TO ANSWER ALL A2 QUESTIONS.
}

void MainClass::A3Main()
{
    //IMPLEMENT CODE TO ANSWER ALL A3 QUESTIONS.
}
