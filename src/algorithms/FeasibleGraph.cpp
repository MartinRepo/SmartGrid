#include <iostream>
#include <vector>
#include <random>

#include "../../include/algorithms/FeasibleGraph.h"

using namespace std;

vector<vector<Edge>> feasibleGraph;

bool compareLoad(const Edge &a, const Edge &b) {
    return a.job.width < b.job.width;
}

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

void executeShift(const vector<int> &path) {
    Job tmpJob = feasibleGraph[path[0]].back().job;
    for (int i = 1; i < path.size(); i++) {
        Job nextJob = feasibleGraph[path[i]].back().job;
        feasibleGraph[path[i - 1]].push_back({path[i], nextJob});
    }
    feasibleGraph[path[0]].push_back({path[0], tmpJob});
}

vector<Config> offlineScheduling(vector<Job> &jobs, int numTimeSlots) {
    int numJobs = jobs.size();

    feasibleGraph.clear();
    feasibleGraph.resize(numTimeSlots);

    // Obtain a random seed from hardware
    std::random_device rd;

    // Seed the random number generator
    std::default_random_engine rng(rd());

    shuffle(jobs.begin(), jobs.end(), rng);

    for (int i = 0; i < numJobs; i++) {
        int bestTimeSlot = 0;
        int minLoad = INT_MAX;
        for (int t = 0; t < numTimeSlots; t++) {
            int currentLoad = 0;
            for (const Edge &e : feasibleGraph[t]) {
                currentLoad += e.job.width;
            }
            if (currentLoad < minLoad) {
                bestTimeSlot = t;
                minLoad = currentLoad;
            }
        }

        for (int t = 0; t < numTimeSlots; t++) {
            if (t == bestTimeSlot) {
                feasibleGraph[t].push_back({bestTimeSlot, jobs[i]});
            }
        }
    }

    for (int t = 0; t < numTimeSlots; t++) {
        vector<int> path;
        vector<bool> visited(numTimeSlots, false);
        for (int t_prime = 0; t_prime < numTimeSlots; t_prime++) {
            if (t_prime != t && findPath(t, t_prime, path, visited)) {
                executeShift(path);
            }
        }
    }

    vector<vector<Job>> schedule(numTimeSlots);
    for (int t = 0; t < numTimeSlots; t++) {
        for (const Edge &e : feasibleGraph[t]) {
            schedule[t].push_back(e.job);
        }
    }
    vector<Config> result;
    for(int t = 0; t < numTimeSlots; t++) {
        for (const Edge &e : feasibleGraph[t]) {
            result.push_back({e.job.id, e.to, e.to+e.job.width});
        }
    }
    return result;
}
