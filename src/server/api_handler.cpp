#include "../../include/server/api_handler.h"
#include "../../include/structs/Job.h"
#include "../../include/algorithms/FixedParameterTractable.h"
#include "../../include/algorithms/FeasibleGraph.h"
#include "../../include/algorithms/Greedy.h"
#include "../../include/algorithms/Genetic.h"

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
                vector<Config> FPTSolution = FindOptimalConfiguration(S1D1);
                int FPTCost = FPTTotalCost(FPTSolution, S1D1, 14, 2);
                result[U("Algorithm")] = json::value::string("Fixed Param Tractable");
                result[U("Dataset")] = json::value::string("scenario 1 dataset 1");
                result[U("Total Power Cost")] = json::value::number(FPTCost);
                results.push_back(result);

                vector<pair<Config, int>> GreedySolution = greedyScheduler(S1D1, 2);
                int GreedyCost = GreedyTotalCost(S1D1, GreedySolution, 14, 2);
                result[U("Algorithm")] = json::value::string("Greedy");
                result[U("Dataset")] = json::value::string("scenario 1 dataset 1");
                result[U("Total Power Cost")] = json::value::number(GreedyCost);
                results.push_back(result);

                vector<Config> FeasibleGraphSolution = offlineScheduling(S1D1, 4);
                int feasibleGraphTotalCost = FeasibleGraphTotalCost(FeasibleGraphSolution, S1D1, 14, 2);
                result[U("Algorithm")] = json::value::string("Feasible Graph");
                result[U("Dataset")] = json::value::string("scenario 1 dataset 1");
                result[U("Total Power Cost")] = json::value::number(feasibleGraphTotalCost);
                results.push_back(result);

                vector<Config> GeneticSolution = geneticAlgorithm(S1D1, 20);
                int geneticTotalCost = GeneticTotalCost(S1D1, GeneticSolution, 14, 2);
                result[U("Algorithm")] = json::value::string("Genetic");
                result[U("Dataset")] = json::value::string("scenario 1 dataset 1");
                result[U("Total Power Cost")] = json::value::number(geneticTotalCost);
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