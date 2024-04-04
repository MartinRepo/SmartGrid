#include <iostream>
#include <vector>
#include "../include/structs/Job.h"
#include "../include/algorithms/FixedParameterTractable.h"
#include "../include/algorithms/FeasibleGraph.h"
#include "../include/algorithms/Greedy.h"
#include "../include/algorithms/Genetic.h"

using namespace std;

int main() {
    vector<Job> Jobs = {
            {0, 1, 14, 1, 2},
            {1, 0, 2, 1, 4},
            {2, 3, 5, 1, 4},
            {3, 4, 8, 1, 1},
            {4, 5, 13, 1, 1},
            {5, 6, 8, 1, 6},
            {6, 7, 8, 1, 1},
            {7, 9, 10, 1, 1},
            {8, 10, 11, 1, 1},
            {9, 11, 13, 1, 1},
            {10, 12, 14, 1, 1}
    };
    // test for fpt
    auto start = chrono::high_resolution_clock::now();
    Table FPTConfiguration = FindOptimalConfiguration(Jobs);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout<<"############## This is the FPT's solution ##############"<<endl;
    for(auto & a : FPTConfiguration) {
        cout<<"Job "<<a.id<<" is scheduled from "<<a.startTime<<" to "<<a.endTime<<endl;
    }
    cout << "Function took " << duration.count() << " ms.\n";
    // test for greedy
    cout<<"############## This is the Greedy's solution ##############"<<endl;
    vector<pair<Config, int>> GreedySolution = greedyScheduler(Jobs, 4);
    for(const auto & a : GreedySolution) {
        cout << "Job "<<a.first.id << " is scheduled on machine " << a.second << " scheduling time is from " << a.first.startTime << " to " << a.first.endTime << endl;
    }
    // test for feasible graph
    cout<<"############## This is the Feasible Graph's solution ##############"<<endl;
    vector<Config> feasible = offlineScheduling(Jobs, Jobs.size());
    for(auto& a : feasible) {
        cout<<"Job "<<a.id<<" is scheduled from "<<a.startTime<<" to "<<a.endTime<<endl;
    }
//    int a = calculateCost(optimalConfiguration, fptJobs, 14, 2);
//    cout << "result cost is " << a << endl;
    cout<<"############## This is the Genetic's solution ##############"<<endl;
    vector<Config> genetic = geneticAlgorithm(Jobs, 20);
    for(auto& a : genetic) {
        cout<<"Job "<<a.id<<" is scheduled from "<<a.startTime<<" to "<<a.endTime<<endl;
    }
    return 0;
}
