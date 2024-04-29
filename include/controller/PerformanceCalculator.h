#ifndef SMARTGRID_PERFORMANCECALCULATOR_H
#define SMARTGRID_PERFORMANCECALCULATOR_H
#include <vector>
#include <cpprest/json.h>
#include "../structs/Config.h"
#include "../structs/Job.h"

using namespace std;
using namespace web;

json::value getTotalCost(const std::string& algorithmName, const std::string& datasetName, vector<Job>& dataset);
json::value getPeakCost(const std::string& algorithmName, const std::string& datasetName, vector<Job>& dataset);
json::value getRunningTime(const std::string& algorithmName, const std::string& datasetName, vector<Job>& dataset);

#endif //SMARTGRID_PERFORMANCECALCULATOR_H
