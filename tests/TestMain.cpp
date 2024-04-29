#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include "../include/structs/Job.h"
#include "../include/algorithms/FixedParameterTractable.h"
#include "../include/algorithms/FeasibleGraph.h"
#include "../include/algorithms/Greedy.h"
#include "../include/algorithms/Genetic.h"
#include "../include/utils/TotalCost.h"
#include "../include/utils/PeakCost.h"

using namespace std;

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

vector<Job> GreedyJobs = {
        {0, 0, 2, 2, 1},
        {1, 0, 2, 2, 1},
        {2, 0, 2, 2, 1},
        {3, 0, 2, 2, 1},
        {4, 2, 4, 2, 1},
        {5, 2, 4, 2, 1},
        {6, 2, 4, 2, 1},
        {7, 3, 5, 2, 1},
        {8, 3, 5, 2, 1},
        {9, 3, 5, 2, 1},
};

vector<Job> GeneticJobs = {
        {0, 0, 2, 1, 1},
        {1, 1, 3, 1, 1},
        {2, 2, 4, 1, 1},
        {3, 3, 5, 1, 1},
};

TEST(UtilsTest, TotalCostTest) {
    Table FPTConfiguration = FindOptimalConfiguration(Jobs);
    int TotalCost = GeneralTotalCost(Jobs, FPTConfiguration, 14, 2);
    EXPECT_EQ(79, TotalCost);
}

TEST(UtilsTest, PeakCostTest) {
    vector<Config> solution = FindOptimalConfiguration(Jobs);
    int PeakCost = GeneralPeakCost(Jobs, solution, 14, 2);
    EXPECT_EQ(36, PeakCost);
}

TEST(AlgoTest, FPTTest){
    cout<<"############## This is the Fixed Parameter Tractable's solution ##############"<<endl;
    vector<Config> solution = FindOptimalConfiguration(Jobs);
    for(auto & a : solution) {
        cout<<"Job "<<a.id<<" is scheduled from "<<a.startTime<<" to "<<a.endTime<<endl;
    }
}

TEST(AlgoTest, GreedyTest){
    cout<<"############## This is the Greedy's solution ##############"<<endl;
    vector<pair<Config, int>> GreedySolution = greedyScheduler(GreedyJobs, 4);
    for(const auto & a : GreedySolution) {
        cout << "Job "<<a.first.id << " is scheduled on machine " << a.second << " scheduled time is from " << a.first.startTime << " to " << a.first.endTime << endl;
    }
}

TEST(AlgoTest, FGTest){
    cout<<"############## This is the Feasible Graph's solution ##############"<<endl;
    vector<Config> feasible = offlineScheduling(Jobs, Jobs.size());
    for(auto& a : feasible) {
        cout<<"Job "<<a.id<<" is scheduled from "<<a.startTime<<" to "<<a.endTime<<endl;
    }
}

TEST(AlgoTest, GeneticTest) {
    cout << "############## This is the Genetic's solution ##############" << endl;
    vector<Config> genetic = geneticAlgorithm(GeneticJobs, 20);
    for (auto &a: genetic) {
        cout << "Job " << a.id << " is scheduled from " << a.startTime << " to " << a.endTime << endl;
    }
}
