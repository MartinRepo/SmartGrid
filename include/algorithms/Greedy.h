#ifndef SMARTGRID_GREEDY_H
#define SMARTGRID_GREEDY_H
#include <queue>

using namespace std;

struct CompareReleaseTime {
    bool operator()(Job a, const Job& b) {
        return a.releaseTime > b.releaseTime;
    }
};

int calculateCost(queue<int>& processor, int power);

int findLowestLoadMachines(vector<queue<int>>& processors);

vector<pair<Config, int>>  greedyScheduler(vector<Job>& jobs, int num_processors);

#endif //SMARTGRID_GREEDY_H
