#ifndef SMARTGRID_HANDELREQ_H
#define SMARTGRID_HANDELREQ_H
#include <vector>
#include <cpprest/json.h>
#include "../structs/Config.h"
#include "../structs/Job.h"

using namespace std;
using namespace web;

vector<vector<json::value>> RunAlgorithms(json::value input);

#endif //SMARTGRID_HANDELREQ_H
