#ifndef SMARTGRID_FIXEDPARAMETERTRACTABLE_H
#define SMARTGRID_FIXEDPARAMETERTRACTABLE_H

#include "../structs/Job.h"
#include "../structs/Config.h"
#include <vector>
#include <set>
#include <utility>

using namespace std;

using Table = vector<Config>;

bool isValid(const Config &config, const Job &job,
             std::pair<int, int> window);

int isCompatible(const std::pair<int, int> &left, const std::pair<int, int> &right,
                 const std::pair<int, int> windowLeft, const std::pair<int, int> windowI,
                 Job job);

std::pair<int, int> concatenate(const std::pair<int, int> &left,
                                const std::pair<int, int> &right, int type);

Table ListConfiguration(std::pair<int, int> window, const std::vector<Job> &maxClique);

Table ConcatenateTables(Table &TLeft, const Table &TRight,
                        std::pair<int, int> windowLeft, std::pair<int, int> windowI,
                        const std::vector<Job> &jobs);

Table FilterTable(const Table &TLeft, const vector<Job> &jobs, const int boundary);

Table FindOptimalConfiguration(const vector<Job> &jobs);

#endif //SMARTGRID_FIXEDPARAMETERTRACTABLE_H
