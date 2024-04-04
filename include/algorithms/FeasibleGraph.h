#ifndef SMARTGRID_FEASIBLEGRAPH_H
#define SMARTGRID_FEASIBLEGRAPH_H

#include <vector>
#include "../structs/Job.h"
#include "../structs/Config.h"

using namespace std;

//struct GraphJob {
//    int id;
//    int load;
//    vector<int> timeslot;
//    // 其他任务属性
//};

struct Edge {
    int to;
    Job job;
};

// 比较函数，用于比较两个可行时刻的负载
bool compareLoad(const Edge &a, const Edge &b);

bool findPath(int start, int end, vector<int> &path, vector<bool> &visited);

void executeShift(const vector<int> &path);

vector<Config> offlineScheduling(vector<Job> &jobs, int numTimeSlots);

#endif //SMARTGRID_FEASIBLEGRAPH_H
