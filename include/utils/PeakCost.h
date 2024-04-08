#ifndef SMARTGRID_PEAKCOST_H
#define SMARTGRID_PEAKCOST_H
#include "../structs/Job.h"
#include "../structs/Config.h"
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

int GeneralPeakCost(const vector<Job> &jobs, const vector<Config> &Solution, const int boundary, const int power);
int GreedyPeakCost(vector<Job> jobs, vector<pair<Config, int>> & Solution, const int boundary, const int power);

#endif //SMARTGRID_PEAKCOST_H
