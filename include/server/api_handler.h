#ifndef SMARTGRID_API_HANDLER_H
#define SMARTGRID_API_HANDLER_H
#include <vector>
#include <cpprest/json.h>
#include "../structs/Config.h"

using namespace std;
using namespace web;

json::value RunAlgorithms(json::value);
#endif //SMARTGRID_API_HANDLER_H
