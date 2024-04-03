#include <iostream>
#include <vector>
#include <random>

#include "../../include/algorithms/FeasibleGraph.h"

using namespace std;

vector<vector<Edge>> feasibleGraph;

// 比较函数，用于比较两个可行时刻的负载
bool compareLoad(const Edge &a, const Edge &b) {
    return a.job.load < b.job.load;
}

// 查找从起点到终点的一条路径
bool findPath(int start, int end, vector<int> &path, vector<bool> &visited) {
    if (start == end) {
        path.push_back(start);
        return true;
    }
    visited[start] = true;
    for (const Edge &e : feasibleGraph[start]) {
        if (!visited[e.to] && findPath(e.to, end, path, visited)) {
            path.push_back(start);
            return true;
        }
    }
    return false;
}

// 执行路径上的移动
void executeShift(const vector<int> &path) {
    GraphJob tmpJob = feasibleGraph[path[0]].back().job;
    for (int i = 1; i < path.size(); i++) {
        GraphJob nextJob = feasibleGraph[path[i]].back().job;
        feasibleGraph[path[i - 1]].push_back({path[i], nextJob});
    }
    feasibleGraph[path[0]].push_back({path[0], tmpJob});
}

// 离线任务调度算法
vector<vector<GraphJob>> offlineScheduling(vector<GraphJob> &jobs, int numTimeSlots) {
    int numJobs = jobs.size();

    feasibleGraph.clear();
    feasibleGraph.resize(numTimeSlots);

    // Obtain a random seed from hardware
    std::random_device rd;

    // Seed the random number generator
    std::default_random_engine rng(rd());

    // 将任务按照某种顺序排列，这里使用随机顺序
    shuffle(jobs.begin(), jobs.end(), rng);

    for (int i = 0; i < numJobs; i++) {
        int bestTimeSlot = 0;
        int minLoad = INT_MAX;
        // 找当前最小负载
        for (int t = 0; t < numTimeSlots; t++) {
            int currentLoad = 0;
            // 计算当前时刻的负载
            for (const Edge &e : feasibleGraph[t]) {
                currentLoad += e.job.load;
            }
            if (currentLoad < minLoad) {
                bestTimeSlot = t;
                minLoad = currentLoad;
            }
        }

        // 更新可行图
        for (int t = 0; t < numTimeSlots; t++) {
            if (t == bestTimeSlot) {
                feasibleGraph[t].push_back({bestTimeSlot, jobs[i]});
            }
        }
    }

    // 检查并执行移动操作
    for (int t = 0; t < numTimeSlots; t++) {
        vector<int> path;
        vector<bool> visited(numTimeSlots, false);
        for (int t_prime = 0; t_prime < numTimeSlots; t_prime++) {
            if (t_prime != t && findPath(t, t_prime, path, visited)) {
                executeShift(path);
            }
        }
    }

    // 从可行图中提取最终的任务调度
    vector<vector<GraphJob>> schedule(numTimeSlots);
    for (int t = 0; t < numTimeSlots; t++) {
        for (const Edge &e : feasibleGraph[t]) {
            schedule[t].push_back(e.job);
        }
    }

    return schedule;
}
