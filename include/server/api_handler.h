#ifndef SMARTGRID_API_HANDLER_H
#define SMARTGRID_API_HANDLER_H
#include <vector>
#include <cpprest/json.h>
#include "../structs/Config.h"
#include "../structs/Job.h"

using namespace std;
using namespace web;

json::value getTotalCost(const std::string& algorithmName, const vector<Job>& dataset);
vector<vector<json::value>> RunAlgorithms(json::value input);
#endif //SMARTGRID_API_HANDLER_H
