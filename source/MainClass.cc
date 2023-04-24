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

// ./Main <Activity> <Question> <<GraphFile> or <-d>> d = default

void MainClass::Main(int argc, char *argv[])
{
    bool argsAreOk = checkArguments(argc, argv);

    if (argsAreOk)
    {
        string Activity = argv[1];
        int Question = stoi(argv[2]);
        string graphFileOrFlag = argv[3];

        bool defaultFlag = false;
        if (graphFileOrFlag == "-d")
        {
            defaultFlag = true;
        }
        else
        {
            defaultFlag = false;
        }

        runActivity(Activity, Question, graphFileOrFlag, defaultFlag);
    }
}

bool MainClass::checkArguments(int argc, char *argv[])
{
    if (argc != 4)
    {
        string errorMessage = "Error: Missing arguments \n"
                              "Usage: ./Main <Activity> <Question> <<GraphFile> or <-d>> \n"
                              "Activity: A1, A2 or A3 \n"
                              "Question: number of the question as in pdf activity file \n"
                              "graphFile: name of the file \n"
                              "-d: A flag that indicates if the default graph will be used";
        cout << errorMessage << endl;

        return false;
    }
    else
    {
        vector<string> validActivities = {"A1", "A2", "A3"};
        map<string, vector<int>> validQuestionsPerActivity = {
            {"A1", {2, 3, 4, 5}},
            {"A2", {1, 2, 3}},
            {"A3", {1, 2, 3}}
        };
        vector<string> validGraphFiles = getInputFiles(argv[1]);

        string activity = argv[1];
        int question = stoi(argv[2]);
        string graphFileOrFlag = argv[3];

        vector<int> validQuestions = validQuestionsPerActivity[activity];

        bool activityIsValid = find_if(validActivities.begin(), validActivities.end(),[&](const std::string& file) { return file == activity; }) != validActivities.end();
        bool graphFileIsValid = find_if(validGraphFiles.begin(), validGraphFiles.end(),[&](const std::string& file) { return file == graphFileOrFlag; }) != validGraphFiles.end();
        bool questionIsValid = find_if(validQuestions.begin(), validQuestions.end(),[&](const int& file) { return file == question; }) != validQuestions.end();
        bool flagIsValid = graphFileOrFlag == "-d" ? true : false;

        if (activityIsValid && questionIsValid && (graphFileIsValid || flagIsValid))
        {   
            return true;
        }
        else
        {
            string errorMessage = "Error: Invalid arguments \n"
                              "Usage: ./Main <Activity> <Question> <<GraphFile> or <-d>> \n"
                              "Activity: A1, A2 or A3 \n"
                              "Question: number of the question as in pdf activity file \n"
                              "graphFile: name of the file \n"
                              "-d: A flag that indicates if the default graph will be used";
            cout << errorMessage << endl;

            return false;
        }
    }
}

vector<string> MainClass::getInputFiles(string activity) {
    DIR* inputFolder;
    struct dirent* folderEntry;

    path current_path = filesystem::current_path();
    string folderPath = string(current_path.c_str()) + "/inputs/" + activity;

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

void MainClass::runActivity(string Activity, int question, string graphFile, bool defaultFlag)
{
    if (Activity == "A1")
    {
        Activities::A1Main(question, graphFile, defaultFlag);
    }
    else if (Activity == "A2")
    {
        Activities::A2Main(question, graphFile, defaultFlag);
    }
    else if (Activity == "A3")
    {
        Activities::A3Main(question, graphFile, defaultFlag);
    }
}
