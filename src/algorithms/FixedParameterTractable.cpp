#include "../../include/algorithms/FixedParameterTractable.h"
#include "../../include/utils/TotalCost.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

bool isValid(const Config &config, const Job &job,
             pair<int, int> window) {
    if (config.startTime >= config.endTime) {
        return false;
    } else if (config.endTime > config.startTime + job.width) {
        return false;
    } else if (config.endTime - config.startTime < min(job.width, window.second - window.first) &&
               config.startTime >= window.first &&
               config.endTime <= window.second) {
        return false;
    } else if (config.startTime < job.releaseTime &&
               config.startTime < window.second) {
        return false;
    } else if (config.endTime > job.deadline &&
               config.endTime > window.first) {
        return false;
    }
    return true;
}

int getCompatibleType(const Config &left, const Config &right, const pair<int, int> windowLeft, const pair<int, int> windowI, Job job) {
    if (left.startTime >= windowLeft.first && left.endTime <= windowLeft.second && right.endTime <= windowI.first) {
        return 1;
    } else if (left.startTime <= windowLeft.first && left.endTime >= windowLeft.second && right.startTime <= windowI.first && right.endTime >= windowI.second) {
        return 2;
    } else if (left.startTime > windowLeft.second && right.startTime > windowI.first) {
        return 3;
    } else {
        return 0;
    }

}

Config concatenate(const Config &left, const Config &right, int type) {
    Config result{};
    result.id = left.id;
    if (type == 1) {
        return left;
    } else if (type == 2) {
        result.startTime = left.startTime;
        result.endTime = right.endTime;
    } else if (type == 3) {
        return right;
    }

    return result;
}

Table ListConfiguration(pair<int, int> window, const vector<Job> &maxClique) {
    Table validConfiguration;
    for (const auto &job : maxClique) {
        for (int i = window.first; i < window.second; i++) {
            Config config{};
            config.id = job.id;
            if (i + job.width <= window.second) {
                config.startTime = i;
                config.endTime = i + job.width;
            } else {
                config.startTime = i;
                config.endTime = window.second + 1;
            }
            if (isValid(config, job, window)) {
                validConfiguration.push_back(config);
            }
        }
    }
    return validConfiguration;
}

Table ConcatenateTables(Table &TLeft, const Table &TRight, pair<int, int> windowLeft, pair<int, int> windowI, const vector<Job> &jobs) {
    for(auto &leftConfig : TLeft) {
        for(const auto &rightConfig : TRight) {
            if(leftConfig.id == rightConfig.id) {
                if(leftConfig.startTime == 0 && leftConfig.endTime == 1) {
                    // this is initialized configuration
                    // 1. [0,1) satisfies job's requirement
                    // 2. [0,1) can be a part of job's execution time
                    if (jobs[leftConfig.id].releaseTime == 0 &&
                        jobs[leftConfig.id].width > 1) {
                        Config tempConfig = {leftConfig.id, leftConfig.startTime, rightConfig.endTime};
                        if (isValid(tempConfig, jobs[leftConfig.id],{windowLeft.first, windowI.second})) {
                            leftConfig.endTime = rightConfig.endTime;
                        }
                    }
                    // 3. the job released after 1.
                    if (jobs[leftConfig.id].releaseTime >= 1) {
                        Config tempConfig = rightConfig;
                        if (isValid(tempConfig, jobs[leftConfig.id],{windowLeft.first, windowI.second})) {
                            leftConfig = rightConfig;
                        }
                    }
                } else {
                    int type = getCompatibleType(leftConfig, rightConfig, windowLeft, windowI, jobs[leftConfig.id]);
                    if (type == 0) {
                        // get error
                    }
                    Config tempConfig = concatenate(leftConfig, rightConfig, type);
                    if (isValid(tempConfig, jobs[leftConfig.id],
                                {windowLeft.first, windowI.second})) {
                        leftConfig = tempConfig;
                    }
                }
            }
        }
    }
    return TLeft;
}

Table FilterTable(const Table &TLeft, const vector<Job> &jobs, const int boundary) {
    Table newTable;
    for (auto & config : TLeft) {
        if(config.startTime != 0 && config.endTime != 1 || (jobs[config.id].releaseTime == 0)) {
            newTable.push_back(config);
        }
    }
//    cout <<"######################################################"<<endl;
    int cost = GeneralTotalCost(jobs, newTable, boundary, 2);
//    cout << newTable.size() <<" jobs have been scheduled, and currently optimal cost is: " << cost << endl;
    return TLeft;
}

// test
void outputTable(Table & table, const vector<Job> &jobs) {
    cout<<"------------Currently Scheduling Solution---------------"<<endl;
    for(auto& config : table) {
        if(config.startTime != 0 && config.endTime != 1 || (jobs[config.id].releaseTime == 0)){
            cout<<"Job "<<config.id<<" executes from "<<config.startTime<<" to "<<config.endTime<<endl;
        }
    }
}

Table FindOptimalConfiguration(const vector<Job> &jobs) {
    vector<vector<Job>> intervalGraph(jobs.size());
    for (int i = 0; i < jobs.size(); i++) {
        for (int j = 0; j < jobs.size(); j++) {
            if (i != j) {
                if ((jobs[i].releaseTime < jobs[j].releaseTime && jobs[i].deadline > jobs[j].releaseTime) ||
                    (jobs[i].releaseTime > jobs[j].releaseTime && jobs[i].releaseTime < jobs[j].deadline)) {
                    intervalGraph[i].push_back(jobs[j]);
                }
            }
        }
    }

    int maxBoundary = 0;
    for(auto & job : jobs) {
        if(job.deadline>maxBoundary) {
            maxBoundary = job.deadline;
        }
    }
    if(maxBoundary%2 != 0) {
        maxBoundary += 1;
    }
    vector<int> boundaries;
    for(int i = 0; i<=maxBoundary; i+=2) {
        boundaries.push_back(i);
    }

    vector<pair<int, int>> windows;
    for(int i = 0; i<boundaries.size()-1; i++) {
        pair<int, int> newWindow = {boundaries[i], boundaries[i+1]};
        windows.push_back(newWindow);
    }

    vector<vector<Job>> cliques(windows.size());
    for(int i = 0; i<windows.size(); i++) {
        for(auto & job : jobs) {
            if(job.releaseTime >= windows[i].first && job.releaseTime <= windows[i].second) {
                cliques[i].push_back(job);
            }
        }
    }

    Table TLeft(jobs.size());
    for (int i = 0; i < jobs.size(); i++) {
        TLeft[i].id = jobs[i].id;
        TLeft[i].startTime = boundaries[0];
        TLeft[i].endTime = boundaries[0] + 1;
    }

    for (int i = 0; i < windows.size(); i++) {
        pair<int, int> windowLeft = {boundaries[0], boundaries[i + 1]};
        Table TRight = ListConfiguration(windows[i], cliques[i]);
        TLeft = ConcatenateTables(TLeft, TRight, windowLeft, windows[i], jobs);
        TLeft = FilterTable(TLeft, jobs, boundaries[boundaries.size()-1]);
//        outputTable(TLeft, jobs);
    }
    return TLeft;
}