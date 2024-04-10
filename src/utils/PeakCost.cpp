#include "../../include/utils/PeakCost.h"

int GeneralPeakCost(const vector<Job> &jobs, const vector<Config> &Solution, const int boundary, const int power) {
    int result = 0;
    for (int i = 0; i < boundary; i++) {
        vector<int> jobSet;
        for (const auto &config : Solution) {
            if (config.startTime <= i && config.endTime > i) {
                jobSet.push_back(config.id);
            }
        }
        int sum = 0;
        for (auto it : jobSet) {
            sum += jobs[it].height;
        }
        if (sum > result) {
            result = sum;
        }
    }
    return pow(result, power);
}

int GreedyPeakCost(vector<Job> jobs, vector<pair<Config, int>> & Solution, const int boundary, const int power) {
    int result = 0;
    for (int i = 0; i < boundary; i++) {
        unordered_map<int, vector<int>> processorJobSet;
        for (const auto & config : Solution) {
            if (config.first.startTime <= i && config.first.endTime > i) {
                processorJobSet[config.second].push_back(config.first.id);
            }
        }
        int sum = 0;
        for (auto it : processorJobSet) {
            for(auto id : it.second){
                sum += jobs[id].height;
            }
        }
        if (sum > result) {
            result = pow(sum, power);
        }
    }
    return result;
}
