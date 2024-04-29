#include <chrono>
#include "../../include/controller/PerformanceCalculator.h"
#include "../../include/algorithms/FixedParameterTractable.h"
#include "../../include/algorithms/FeasibleGraph.h"
#include "../../include/algorithms/Greedy.h"
#include "../../include/algorithms/Genetic.h"
#include "../../include/utils/TotalCost.h"
#include "../../include/utils/PeakCost.h"

json::value getTotalCost(const std::string& algorithmName, const std::string& datasetName, vector<Job>& dataset) {
    cout<<"Start calculating total cost for "<<algorithmName<<endl;
    vector<Config> solution;
    int totalCost = 0;

    if (algorithmName == "Fixed Param Tractable") {
        solution = FindOptimalConfiguration(dataset);
    } else if (algorithmName == "Feasible Graph") {
        solution = offlineScheduling(dataset, 4);
    } else if (algorithmName == "Genetic") {
        solution = geneticAlgorithm(dataset, 20);
    } else if (algorithmName == "Greedy") {
        vector<pair<Config, int>> GreedySolution = greedyScheduler(dataset, 2);
        totalCost = GreedyTotalCost(dataset, GreedySolution, 14, 2);
        json::value result;
        result[U("algorithm")] = json::value::string(algorithmName);
        result[U("dataset")] = json::value::string(datasetName);
        result[U("Total Power Cost")] = json::value::number(totalCost);
        return result;
    }

    totalCost = GeneralTotalCost(dataset, solution, 14, 2);

    json::value result;
    result[U("algorithm")] = json::value::string(algorithmName);
    result[U("dataset")] = json::value::string(datasetName);
    result[U("Total Power Cost")] = json::value::number(totalCost);
    cout<<"Calculating total cost completed"<<endl;
    return result;
}

json::value getPeakCost(const std::string& algorithmName, const std::string& datasetName, vector<Job>& dataset) {
    cout<<"Start calculating peak cost for "<<algorithmName<<endl;
    vector<Config> solution;
    int peakCost = 0;

    if (algorithmName == "Fixed Param Tractable") {
        solution = FindOptimalConfiguration(dataset);
    } else if (algorithmName == "Feasible Graph") {
        solution = offlineScheduling(dataset, 4);
    } else if (algorithmName == "Genetic") {
        solution = geneticAlgorithm(dataset, 20);
    } else if (algorithmName == "Greedy") {
        vector<pair<Config, int>> GreedySolution = greedyScheduler(dataset, 2);
        peakCost = GreedyPeakCost(dataset, GreedySolution, 14, 2);
        json::value result;
        result[U("algorithm")] = json::value::string(algorithmName);
        result[U("dataset")] = json::value::string(datasetName);
        result[U("Peak Power Cost")] = json::value::number(peakCost);
        return result;
    }

    peakCost = GeneralPeakCost(dataset, solution, 14, 2);

    json::value result;
    result[U("algorithm")] = json::value::string(algorithmName);
    result[U("dataset")] = json::value::string(datasetName);
    result[U("Peak Power Cost")] = json::value::number(peakCost);
    cout<<"Calculating peak cost completed"<<endl;
    return result;
}

json::value getRunningTime(const std::string& algorithmName, const std::string& datasetName, vector<Job>& dataset) {
    cout<<"Start calculating running time for "<<algorithmName<<endl;
    auto start = std::chrono::high_resolution_clock::now();
    if (algorithmName == "Fixed Param Tractable") {
        vector<Config> solution = FindOptimalConfiguration(dataset);
    } else if (algorithmName == "Feasible Graph") {
        vector<Config> solution = offlineScheduling(dataset, 4);
    } else if (algorithmName == "Genetic") {
        vector<Config> solution = geneticAlgorithm(dataset, 20);
    } else if (algorithmName == "Greedy") {
        vector<pair<Config, int>> GreedySolution = greedyScheduler(dataset, 2);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    json::value result;
    result[U("algorithm")] = json::value::string(algorithmName);
    result[U("dataset")] = json::value::string(datasetName);
    result[U("Running Time /µs")] = json::value::number(duration.count());
    cout<<"Calculating running time completed"<<endl;
    return result;
}
