#include <chrono>
#include "../../include/controller/HandelReq.h"
#include "../../include/controller/PerformanceCalculator.h"

void executeAlgorithm(vector<Job>& jobs, vector<vector<json::value>>& results, string scenario, int type) {
    json::value result = json::value::object();
    scenario = scenario + " D" + to_string(type);
    result = getTotalCost("Fixed Param Tractable", scenario, jobs);
    results[0].push_back(result);
    result = getTotalCost("Feasible Graph", scenario, jobs);
    results[0].push_back(result);
    result = getTotalCost("Greedy", scenario, jobs);
    results[0].push_back(result);
    result = getTotalCost("Genetic", scenario, jobs);
    results[0].push_back(result);
    // get peak cost
    result = getPeakCost("Fixed Param Tractable", scenario, jobs);
    results[1].push_back(result);
    result = getPeakCost("Feasible Graph", scenario, jobs);
    results[1].push_back(result);
    result = getPeakCost("Greedy", scenario, jobs);
    results[1].push_back(result);
    result = getPeakCost("Genetic", scenario, jobs);
    results[1].push_back(result);
    // get running time
    result = getRunningTime("Fixed Param Tractable", scenario, jobs);
    results[2].push_back(result);
    result = getRunningTime("Feasible Graph", scenario, jobs);
    results[2].push_back(result);
    result = getRunningTime("Greedy", scenario, jobs);
    results[2].push_back(result);
    result = getRunningTime("Genetic", scenario, jobs);
    results[2].push_back(result);
}

vector<Job> parseJobSet(const json::array& jobSet) {
    vector<Job> jobs;
    for (const auto& job : jobSet) {
        Job newJob{
                job.at(U("id")).as_integer(),
                job.at(U("releaseTime")).as_integer(),
                job.at(U("deadline")).as_integer(),
                job.at(U("width")).as_integer(),
                job.at(U("height")).as_integer()
        };

        jobs.push_back(newJob);
    }
    return jobs;
}

vector<vector<json::value>> RunAlgorithms(json::value input) {
    cout<<"Start running algorithms..."<<endl;
    if (!input[U("selectedValues")].is_array()) {
        throw std::runtime_error("Input should be an array of job objects.");
    }

    vector<vector<json::value>> results(3);
    for (const auto& element : input[U("selectedValues")].as_array()) {
        const auto& scenario = element.at(0).as_string();
        const auto& jobSets = element.at(1).as_array();
        int type = 1;

        for (const auto& jobSet : jobSets) {
            auto jobs = parseJobSet(jobSet.as_array());
            executeAlgorithm(jobs, results, scenario, type);
            type++;
        }
    }
    return results;
}
//    } else {
//        // input json is unexpected
//        vector<vector<json::value>> error;
//        json::value throwError = json::value::object();
//        throwError[U("error")] = json::value::string(U("Error input or 'selectedValues' empty"));
//        error[0].push_back(throwError);
//        return error;
//    }