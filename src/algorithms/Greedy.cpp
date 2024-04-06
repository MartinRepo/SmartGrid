#include "../../include/algorithms/Greedy.h"
#include <unordered_map>

int calculateCost(queue<int>& processor, int power) {
    int load = pow(processor.size(), power);
    return load;
}

int findLowestLoadMachines(vector<queue<int>>& processors) {
    int min = INT_MAX;
    int min_index = -1;
    int cost;
    for (int i = 0; i<processors.size(); i++) {
        cost = calculateCost(processors[i], 2);
        if (cost<min) {
            min = cost;
            min_index = i;
        }
    }
    return min_index;
}

int GreedyTotalCost(vector<Job> jobs, vector<pair<Config, int>> & Solution, const int boundary, const int power) {
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
        result += pow(sum, power);
    }
    return result;
}

vector<pair<Config, int>> greedyScheduler(vector<Job>& jobs, int num_processors) {

    vector<queue<int>> processors(num_processors);

    priority_queue<Job, vector<Job>, CompareReleaseTime> jobQueue;
    for(auto& job : jobs){
        jobQueue.push(job);
    }

    int time = 0;
    vector<pair<Config, int>> ans;
    while(!jobQueue.empty()){
        int currentJobReleaseTime = jobQueue.top().releaseTime;
        for(auto & processor : processors) {
            if(!processor.empty()) {
                processor.pop();
            }
        }
        if (time >= currentJobReleaseTime) {
            while(!jobQueue.empty()) {
                int machineIndex = findLowestLoadMachines(processors);
                Job newJob = jobQueue.top();
                processors[machineIndex].push(newJob.id);
                Config config{newJob.id, time, time+newJob.width};
                ans.emplace_back(config, machineIndex);
                jobQueue.pop();
                if (jobQueue.top().releaseTime > time) {
                    break;
                }
            }
        }
        time++;
    }
    return ans;
}
