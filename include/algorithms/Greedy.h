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

int findLowestLoadMachines(vector<queue<int>>& processors, vector<Job>& jobs, int power);

vector<pair<Config, int>>  greedyScheduler(vector<Job>& jobs, int num_processors);

#endif //SMARTGRID_GREEDY_H
