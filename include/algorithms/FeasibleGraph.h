#ifndef SMARTGRID_FEASIBLEGRAPH_H
#define SMARTGRID_FEASIBLEGRAPH_H

#include <vector>
#include <climits>
#include "../structs/Job.h"
#include "../structs/Config.h"

using namespace std;

struct Edge {
    int to;
    Job job;
};

bool compareLoad(const Edge &a, const Edge &b);

bool findPath(int start, int end, vector<int> &path, vector<bool> &visited);

void executeShift(const vector<int> &path);

vector<Config> offlineScheduling(vector<Job> &jobs, int numTimeSlots);

#endif //SMARTGRID_FEASIBLEGRAPH_H
