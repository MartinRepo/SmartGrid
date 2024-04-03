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
    Table FPTConfiguration = FindOptimalConfiguration(Jobs);
    cout<<"############## This is the final optimal solution ##############"<<endl;
    for(auto & a : FPTConfiguration) {
        cout<<"Job "<<a.id<<" is scheduled from "<<a.startTime<<" to "<<a.endTime<<endl;
    }
    // test for greedy
    vector<pair<Config, int>> GreedySolution = greedyScheduler(Jobs, 4);
    for(const auto & a : GreedySolution) {
        cout << "Job "<<a.first.id << " is scheduled on machine " << a.second << " scheduling time is from " << a.first.startTime << " to " << a.first.endTime << endl;
    }

//    int a = calculateCost(optimalConfiguration, fptJobs, 14, 2);
//    cout << "result cost is " << a << endl;
//    vector<GeneticJob> geneticJobs = {
//            {0, 1, 3, 0, 0, 2},
//            {1, 1, 4, 0, 0, 3},
//            {2, 0, 2, 0, 0, 1},
//            {3, 2, 5, 0, 0, 1},
//    };
//    geneticAlgorithm(geneticJobs, 20);
    return 0;
}
