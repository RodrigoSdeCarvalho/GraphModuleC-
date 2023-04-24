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

#include "Activities.h"

using namespace std;

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

            static unique_ptr<GraphModule::UndirectedGraph> getUndirectedGraph(string graphFilePath);

            static unique_ptr<GraphModule::DirectedGraph> getDirectedGraph(string graphFilePath);

            static void buildUndirectedGraphFromInputFile(GraphModule::UndirectedGraph* graph, string inputFilePath);

            static void buildDirectedGraphFromInputFile(GraphModule::DirectedGraph* graph, string inputFilePath);
            
            static string checkGraphKindFromInputFile(string graphFilePath);
    };
}

#endif