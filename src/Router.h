#pragma once

#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Wires.h"
#include "Cell.h"
#include "Endpoint.h"
#include "Circuit.h"

class Router {
public:
    static void route(Circuit& circuit, const ConnectionsMap& conns);
    static void writeSizeInJSON(json& j, int width, int height);
};

