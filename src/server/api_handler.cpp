#include "../../include/server/api_handler.h"
#include "../../include/structs/Job.h"
#include "../../include/algorithms/FixedParameterTractable.h"
#include "../../include/algorithms/FeasibleGraph.h"
#include "../../include/algorithms/Greedy.h"
#include "../../include/algorithms/Genetic.h"
#include "../../include/utils/TotalCost.h"

json::value executeAlgorithms(const std::string& algorithmName, const std::string& datasetName, vector<Job>& dataset) {
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
        result[U("Algorithm")] = json::value::string(algorithmName);
        result[U("Dataset")] = json::value::string(datasetName);
        result[U("Total Power Cost")] = json::value::number(totalCost);
        return result;
    }

    totalCost = GeneralTotalCost(dataset, solution, 14, 2); // 假设这个函数可以接受任何类型的解决方案

    json::value result;
    result[U("Algorithm")] = json::value::string(algorithmName);
    result[U("Dataset")] = json::value::string(datasetName);
    result[U("Total Power Cost")] = json::value::number(totalCost);
    return result;
}

vector<json::value> RunAlgorithms(json::value input) {
    vector<Job> S1D1 = {
            {0, 1, 14, 1, 1},
            {1, 0, 2, 1, 1},
            {2, 3, 5, 1, 1},
            {3, 4, 8, 1, 1},
            {4, 5, 13, 1, 1},
            {5, 6, 8, 1, 1},
            {6, 7, 8, 1, 1},
            {7, 9, 10, 1, 1},
            {8, 10, 11, 1, 1},
            {9, 11, 13, 1, 1},
            {10, 12, 14, 1, 1}
    };
    vector<Job> S2D1 = {
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
    vector<Job> S3D1 = {
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
    vector<Job> S4D1 = {
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
    if (input.has_field(U("selectedValues")) && input[U("selectedValues")].is_array()) {
        auto values = input[U("selectedValues")].as_array();

        vector<utility::string_t> datasets;
        for (auto& value : values) {
            if (value.is_string()) {
                datasets.push_back(value.as_string());
            }
        }
        vector<json::value> results;
        json::value result = json::value::object();
        for(auto& dataset : datasets) {
            if(dataset == "scenario 1 dataset 1"){
                // execute 4 algorithms on S1D1
                result = executeAlgorithms("Fixed Param Tractable", "scenario 1 dataset 1", S1D1);
                results.push_back(result);
                result = executeAlgorithms("Feasible Graph", "scenario 1 dataset 1", S1D1);
                results.push_back(result);
                result = executeAlgorithms("Greedy", "scenario 1 dataset 1", S1D1);
                results.push_back(result);
                result = executeAlgorithms("Genetic", "scenario 1 dataset 1", S1D1);
                results.push_back(result);
            } else if (dataset == "scenario 2 dataset 1"){
                // execute 4 algorithms on S2D1
                result = executeAlgorithms("Fixed Param Tractable", "scenario 2 dataset 1", S2D1);
                results.push_back(result);
                result = executeAlgorithms("Feasible Graph", "scenario 2 dataset 1", S2D1);
                results.push_back(result);
                result = executeAlgorithms("Greedy", "scenario 2 dataset 1", S2D1);
                results.push_back(result);
                result = executeAlgorithms("Genetic", "scenario 2 dataset 1", S2D1);
                results.push_back(result);
            } else if (dataset == "scenario 3 dataset 1"){
                // execute 4 algorithms on S3D1
                result = executeAlgorithms("Fixed Param Tractable", "scenario 3 dataset 1", S3D1);
                results.push_back(result);
                result = executeAlgorithms("Feasible Graph", "scenario 3 dataset 1", S3D1);
                results.push_back(result);
                result = executeAlgorithms("Greedy", "scenario 3 dataset 1", S3D1);
                results.push_back(result);
                result = executeAlgorithms("Genetic", "scenario 3 dataset 1", S3D1);
                results.push_back(result);
            } else if (dataset == "scenario 4 dataset 1"){
                // execute 4 algorithms on S4D1
                result = executeAlgorithms("Fixed Param Tractable", "scenario 4 dataset 1", S4D1);
                results.push_back(result);
                result = executeAlgorithms("Feasible Graph", "scenario 4 dataset 1", S4D1);
                results.push_back(result);
                result = executeAlgorithms("Greedy", "scenario 4 dataset 1", S4D1);
                results.push_back(result);
                result = executeAlgorithms("Genetic", "scenario 4 dataset 1", S4D1);
                results.push_back(result);
            }
        }
        return results;
    } else {
        // input json is unexpected
        vector<json::value> error;
        json::value throwError = json::value::object();
        throwError[U("error")] = json::value::string(U("输入格式错误或缺少'selectedValues'键"));
        error.push_back(throwError);
        return error;
    }
}