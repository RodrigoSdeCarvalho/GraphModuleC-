#ifndef Activities_h
#define Activities_h

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

using namespace std;
using namespace filesystem;

namespace GraphModule
{
    class UndirectedGraph;
    class DirectedGraph;
}

namespace GraphActivity
{
    class Activities
    {
        public:
            static void A1Main(int question, string graphFile, bool defaultFlag);

            static void runA1(int question, string graphFile);

            static void A2Main(int question, string graphFile, bool defaultFlag);

            static void runA2(int question, string graphFile);

            static void A3Main(int question, string graphFile, bool defaultFlag);

            static void runA3(int question, string graphFile);

            static void buildGraphFromInputFile(GraphModule::UndirectedGraph* graph, string inputFilePath);

            static void buildGraphFromInputFile(GraphModule::DirectedGraph* graph, string inputFilePath);

            static void checkGraphKindFromInputFile(string graphFilePath, string expectedKind);

            template <typename Graph>
            static unique_ptr<Graph> buildGraph(string graphFilePath);
    };
}

// Inline in header because of templates.
template <typename Graph>
unique_ptr<Graph> GraphActivity::Activities::buildGraph(string graphFilePath)
{
    path current_path = filesystem::current_path();
    string file_path = string(current_path.c_str()) + "/inputs/" + graphFilePath;

    Graph* graph = new Graph();
    buildGraphFromInputFile(graph, file_path);

    unique_ptr<Graph> graphUniquePtr(graph);

    return graphUniquePtr;
}

#endif