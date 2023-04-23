#ifndef MainClass_h
#define MainClass_h

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace GraphModule
{
    class Graph;
}

namespace GraphActivity
{

    class MainClass
    {
        public:
            static void Main(int argc, char *argv[]);
            static bool checkArguments(int argc, char *argv[]);
            static vector<string> getInputFiles();
            static void runActivity(string Activity, string graphFile);
            static void A1Main(string graphFile);
            static void A2Main(string graphFile);
            static void A3Main(string graphFile);
            static unique_ptr<GraphModule::Graph> getGraph(string graphFile);
            static void buildGraphFromInputFile(GraphModule::Graph* graph, string graphFile);
    };
}

#endif,
