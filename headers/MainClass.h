#ifndef MainClass_h
#define MainClass_h

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace GraphModule
{
    class UndirectedGraph;
    class DirectedGraph;
}

namespace GraphActivity
{

    class MainClass
    {
        public:
            static void Main(int argc, char *argv[]);

            static bool checkArguments(int argc, char *argv[]);

            static vector<string> getInputFiles(string activity);

            static void runActivity(string Activity, int Question, string graphFile, bool defaultFlag);
    };
}

#endif,
