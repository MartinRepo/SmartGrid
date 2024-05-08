#include "../../include/algorithms/Greedy.h"
#include <algorithm>
#include <climits>
#include <cmath>

int findLowestLoadMachines(vector<queue<int>>& processors, vector<Job>& jobs, int power) {
    int min = INT_MAX;
    int min_index = -1;
    int cost;
    for (int i = 0; i<processors.size(); i++) {
        int height = 0;
        queue<int> processor_copy = processors[i];
        while(!processor_copy.empty()){
            for(auto & job : jobs) {
                if(processor_copy.front() == job.id){
                    height+=job.height;
                }
            }
            processor_copy.pop();
        }
        cost = pow(height, power);
        if (cost<min) {
            min = cost;
            min_index = i;
        }
    }
    return min_index;
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
                int machineIndex = findLowestLoadMachines(processors, jobs, 2);
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
