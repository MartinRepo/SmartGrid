#include <chrono>
#include "../../include/controller/HandelReq.h"
#include "../../include/controller/PerformanceCalculator.h"

vector<vector<json::value>> RunAlgorithms(json::value input) {
    cout<<"Start running algorithms..."<<endl;
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
            {0, 1, 14, 4, 1},
            {1, 0, 2, 1, 1},
            {2, 3, 5, 1, 1},
            {3, 4, 8, 2, 1},
            {4, 5, 13, 3, 1},
            {5, 6, 8, 1, 1},
            {6, 7, 8, 1, 1},
            {7, 9, 10, 1, 1},
            {8, 10, 11, 1, 1},
            {9, 11, 13, 1, 1},
            {10, 12, 14, 1, 1}
    };
    vector<Job> S4D1 = {
            {0, 1, 14, 4, 2},
            {1, 0, 2, 1, 4},
            {2, 3, 5, 1, 4},
            {3, 4, 8, 2, 1},
            {4, 5, 13, 3, 1},
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
        vector<vector<json::value>> results(3);
        json::value result = json::value::object();
        for(auto& dataset : datasets) {
            if(dataset == "scenario 1 dataset 1"){
                // execute 4 algorithms on S1D1, get total cost
                result = getTotalCost("Fixed Param Tractable", "scenario 1 dataset 1", S1D1);
                results[0].push_back(result);
                result = getTotalCost("Feasible Graph", "scenario 1 dataset 1", S1D1);
                results[0].push_back(result);
                result = getTotalCost("Greedy", "scenario 1 dataset 1", S1D1);
                results[0].push_back(result);
                result = getTotalCost("Genetic", "scenario 1 dataset 1", S1D1);
                results[0].push_back(result);
                // get peak cost
                result = getPeakCost("Fixed Param Tractable", "scenario 1 dataset 1", S1D1);
                results[1].push_back(result);
                result = getPeakCost("Feasible Graph", "scenario 1 dataset 1", S1D1);
                results[1].push_back(result);
                result = getPeakCost("Greedy", "scenario 1 dataset 1", S1D1);
                results[1].push_back(result);
                result = getPeakCost("Genetic", "scenario 1 dataset 1", S1D1);
                results[1].push_back(result);
                // get running time
                result = getRunningTime("Fixed Param Tractable", "scenario 1 dataset 1", S1D1);
                results[2].push_back(result);
                result = getRunningTime("Feasible Graph", "scenario 1 dataset 1", S1D1);
                results[2].push_back(result);
                result = getRunningTime("Greedy", "scenario 1 dataset 1", S1D1);
                results[2].push_back(result);
                result = getRunningTime("Genetic", "scenario 1 dataset 1", S1D1);
                results[2].push_back(result);
            } else if (dataset == "scenario 2 dataset 1"){
                // execute 4 algorithms on S2D1
                result = getTotalCost("Fixed Param Tractable", "scenario 2 dataset 1", S2D1);
                results[0].push_back(result);
                result = getTotalCost("Feasible Graph", "scenario 2 dataset 1", S2D1);
                results[0].push_back(result);
                result = getTotalCost("Greedy", "scenario 2 dataset 1", S2D1);
                results[0].push_back(result);
                result = getTotalCost("Genetic", "scenario 2 dataset 1", S2D1);
                results[0].push_back(result);
                result = getPeakCost("Fixed Param Tractable", "scenario 2 dataset 1", S2D1);
                results[1].push_back(result);
                result = getPeakCost("Feasible Graph", "scenario 2 dataset 1", S2D1);
                results[1].push_back(result);
                result = getPeakCost("Greedy", "scenario 2 dataset 1", S2D1);
                results[1].push_back(result);
                result = getPeakCost("Genetic", "scenario 2 dataset 1", S2D1);
                results[1].push_back(result);
                result = getRunningTime("Fixed Param Tractable", "scenario 2 dataset 1", S2D1);
                results[2].push_back(result);
                result = getRunningTime("Feasible Graph", "scenario 2 dataset 1", S2D1);
                results[2].push_back(result);
                result = getRunningTime("Greedy", "scenario 2 dataset 1", S2D1);
                results[2].push_back(result);
                result = getRunningTime("Genetic", "scenario 2 dataset 1", S2D1);
                results[2].push_back(result);
            } else if (dataset == "scenario 3 dataset 1"){
                // execute 4 algorithms on S3D1
                result = getTotalCost("Fixed Param Tractable", "scenario 3 dataset 1", S3D1);
                results[0].push_back(result);
                result = getTotalCost("Feasible Graph", "scenario 3 dataset 1", S3D1);
                results[0].push_back(result);
                result = getTotalCost("Greedy", "scenario 3 dataset 1", S3D1);
                results[0].push_back(result);
                result = getTotalCost("Genetic", "scenario 3 dataset 1", S3D1);
                results[0].push_back(result);
                result = getPeakCost("Fixed Param Tractable", "scenario 3 dataset 1", S3D1);
                results[1].push_back(result);
                result = getPeakCost("Feasible Graph", "scenario 3 dataset 1", S3D1);
                results[1].push_back(result);
                result = getPeakCost("Greedy", "scenario 3 dataset 1", S3D1);
                results[1].push_back(result);
                result = getPeakCost("Genetic", "scenario 3 dataset 1", S3D1);
                results[1].push_back(result);
                result = getRunningTime("Fixed Param Tractable", "scenario 3 dataset 1", S3D1);
                results[2].push_back(result);
                result = getRunningTime("Feasible Graph", "scenario 3 dataset 1", S3D1);
                results[2].push_back(result);
                result = getRunningTime("Greedy", "scenario 3 dataset 1", S3D1);
                results[2].push_back(result);
                result = getRunningTime("Genetic", "scenario 3 dataset 1", S3D1);
                results[2].push_back(result);
            } else if (dataset == "scenario 4 dataset 1"){
                // execute 4 algorithms on S4D1
                result = getTotalCost("Fixed Param Tractable", "scenario 4 dataset 1", S4D1);
                results[0].push_back(result);
                result = getTotalCost("Feasible Graph", "scenario 4 dataset 1", S4D1);
                results[0].push_back(result);
                result = getTotalCost("Greedy", "scenario 4 dataset 1", S4D1);
                results[0].push_back(result);
                result = getTotalCost("Genetic", "scenario 4 dataset 1", S4D1);
                results[0].push_back(result);
                result = getPeakCost("Fixed Param Tractable", "scenario 4 dataset 1", S4D1);
                results[1].push_back(result);
                result = getPeakCost("Feasible Graph", "scenario 4 dataset 1", S4D1);
                results[1].push_back(result);
                result = getPeakCost("Greedy", "scenario 4 dataset 1", S4D1);
                results[1].push_back(result);
                result = getPeakCost("Genetic", "scenario 4 dataset 1", S4D1);
                results[1].push_back(result);
                result = getRunningTime("Fixed Param Tractable", "scenario 4 dataset 1", S4D1);
                results[2].push_back(result);
                result = getRunningTime("Feasible Graph", "scenario 4 dataset 1", S4D1);
                results[2].push_back(result);
                result = getRunningTime("Greedy", "scenario 4 dataset 1", S4D1);
                results[2].push_back(result);
                result = getRunningTime("Genetic", "scenario 4 dataset 1", S4D1);
                results[2].push_back(result);
            } else if (dataset == "scenario 1 dataset 2"){
                // execute 4 algorithms on S1D1
                result = getTotalCost("Fixed Param Tractable", "scenario 1 dataset 2", S1D1);
                results[0].push_back(result);
                result = getTotalCost("Feasible Graph", "scenario 1 dataset 2", S1D1);
                results[0].push_back(result);
                result = getTotalCost("Greedy", "scenario 1 dataset 2", S1D1);
                results[0].push_back(result);
                result = getTotalCost("Genetic", "scenario 1 dataset 2", S1D1);
                results[0].push_back(result);
                result = getPeakCost("Fixed Param Tractable", "scenario 1 dataset 2", S1D1);
                results[1].push_back(result);
                result = getPeakCost("Feasible Graph", "scenario 1 dataset 2", S1D1);
                results[1].push_back(result);
                result = getPeakCost("Greedy", "scenario 1 dataset 2", S1D1);
                results[1].push_back(result);
                result = getPeakCost("Genetic", "scenario 1 dataset 2", S1D1);
                results[1].push_back(result);
                result = getRunningTime("Fixed Param Tractable", "scenario 1 dataset 2", S1D1);
                results[2].push_back(result);
                result = getRunningTime("Feasible Graph", "scenario 1 dataset 2", S1D1);
                results[2].push_back(result);
                result = getRunningTime("Greedy", "scenario 1 dataset 2", S1D1);
                results[2].push_back(result);
                result = getRunningTime("Genetic", "scenario 1 dataset 2", S1D1);
                results[2].push_back(result);
            } else if (dataset == "scenario 2 dataset 2"){
                // execute 4 algorithms on S2D1
                result = getTotalCost("Fixed Param Tractable", "scenario 2 dataset 2", S2D1);
                results[0].push_back(result);
                result = getTotalCost("Feasible Graph", "scenario 2 dataset 2", S2D1);
                results[0].push_back(result);
                result = getTotalCost("Greedy", "scenario 2 dataset 2", S2D1);
                results[0].push_back(result);
                result = getTotalCost("Genetic", "scenario 2 dataset 2", S2D1);
                results[0].push_back(result);
                result = getPeakCost("Fixed Param Tractable", "scenario 2 dataset 2", S2D1);
                results[1].push_back(result);
                result = getPeakCost("Feasible Graph", "scenario 2 dataset 2", S2D1);
                results[1].push_back(result);
                result = getPeakCost("Greedy", "scenario 2 dataset 2", S2D1);
                results[1].push_back(result);
                result = getPeakCost("Genetic", "scenario 2 dataset 2", S2D1);
                results[1].push_back(result);
                result = getRunningTime("Fixed Param Tractable", "scenario 2 dataset 2", S2D1);
                results[2].push_back(result);
                result = getRunningTime("Feasible Graph", "scenario 2 dataset 2", S2D1);
                results[2].push_back(result);
                result = getRunningTime("Greedy", "scenario 2 dataset 2", S2D1);
                results[2].push_back(result);
                result = getRunningTime("Genetic", "scenario 2 dataset 2", S2D1);
                results[2].push_back(result);
            } else if (dataset == "scenario 3 dataset 2"){
                // execute 4 algorithms on S3D1
                result = getTotalCost("Fixed Param Tractable", "scenario 3 dataset 2", S3D1);
                results[0].push_back(result);
                result = getTotalCost("Feasible Graph", "scenario 3 dataset 2", S3D1);
                results[0].push_back(result);
                result = getTotalCost("Greedy", "scenario 3 dataset 2", S3D1);
                results[0].push_back(result);
                result = getTotalCost("Genetic", "scenario 3 dataset 2", S3D1);
                results[0].push_back(result);
                result = getPeakCost("Fixed Param Tractable", "scenario 3 dataset 2", S3D1);
                results[1].push_back(result);
                result = getPeakCost("Feasible Graph", "scenario 3 dataset 2", S3D1);
                results[1].push_back(result);
                result = getPeakCost("Greedy", "scenario 3 dataset 2", S3D1);
                results[1].push_back(result);
                result = getPeakCost("Genetic", "scenario 3 dataset 2", S3D1);
                results[1].push_back(result);
                result = getRunningTime("Fixed Param Tractable", "scenario 3 dataset 2", S3D1);
                results[2].push_back(result);
                result = getRunningTime("Feasible Graph", "scenario 3 dataset 2", S3D1);
                results[2].push_back(result);
                result = getRunningTime("Greedy", "scenario 3 dataset 2", S3D1);
                results[2].push_back(result);
                result = getRunningTime("Genetic", "scenario 3 dataset 2", S3D1);
                results[2].push_back(result);
            } else if (dataset == "scenario 4 dataset 2"){
                // execute 4 algorithms on S4D1
                result = getTotalCost("Fixed Param Tractable", "scenario 4 dataset 2", S4D1);
                results[0].push_back(result);
                result = getTotalCost("Feasible Graph", "scenario 4 dataset 2", S4D1);
                results[0].push_back(result);
                result = getTotalCost("Greedy", "scenario 4 dataset 2", S4D1);
                results[0].push_back(result);
                result = getTotalCost("Genetic", "scenario 4 dataset 2", S4D1);
                results[0].push_back(result);
                result = getPeakCost("Fixed Param Tractable", "scenario 4 dataset 2", S4D1);
                results[1].push_back(result);
                result = getPeakCost("Feasible Graph", "scenario 4 dataset 2", S4D1);
                results[1].push_back(result);
                result = getPeakCost("Greedy", "scenario 4 dataset 2", S4D1);
                results[1].push_back(result);
                result = getPeakCost("Genetic", "scenario 4 dataset 2", S4D1);
                results[1].push_back(result);
                result = getRunningTime("Fixed Param Tractable", "scenario 4 dataset 2", S4D1);
                results[2].push_back(result);
                result = getRunningTime("Feasible Graph", "scenario 4 dataset 2", S4D1);
                results[2].push_back(result);
                result = getRunningTime("Greedy", "scenario 4 dataset 2", S4D1);
                results[2].push_back(result);
                result = getRunningTime("Genetic", "scenario 4 dataset 2", S4D1);
                results[2].push_back(result);
            }
        }
        cout<<"Algorithms executed successfully, return result..."<<endl;
        return results;
    } else {
        // input json is unexpected
        vector<vector<json::value>> error;
        json::value throwError = json::value::object();
        throwError[U("error")] = json::value::string(U("Error input or 'selectedValues' empty"));
        error[0].push_back(throwError);
        return error;
    }
}