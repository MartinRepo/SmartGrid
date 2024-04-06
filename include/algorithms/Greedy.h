#ifndef SMARTGRID_GREEDY_H
#define SMARTGRID_GREEDY_H
#include <queue>
#include "../../include/structs/Job.h"
#include "../../include/structs/Config.h"

using namespace std;

struct CompareReleaseTime {
    bool operator()(Job a, const Job& b) {
        return a.releaseTime > b.releaseTime;
    }
};

int calculateCost(queue<int>& processor, int power);

int findLowestLoadMachines(vector<queue<int>>& processors);

int GreedyTotalCost(vector<Job> jobs, vector<pair<Config, int>> & Solution, const int boundary, const int power);

vector<pair<Config, int>>  greedyScheduler(vector<Job>& jobs, int num_processors);

#endif //SMARTGRID_GREEDY_H
