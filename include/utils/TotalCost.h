#ifndef SMARTGRID_TOTALCOST_H
#define SMARTGRID_TOTALCOST_H

#include "../structs/Job.h"
#include "../structs/Config.h"
#include <vector>

using namespace std;

int GeneralTotalCost(const vector<Job> &jobs, const vector<Config> &Solution, const int boundary, const int power);

int GreedyTotalCost(vector<Job> jobs, vector<pair<Config, int>> & Solution, const int boundary, const int power);

#endif //SMARTGRID_TOTALCOST_H
