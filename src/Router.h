#pragma once

#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Wires.h"
#include "Cell.h"
#include "Endpoint.h"

class Router {
public:
    static Wires route(const CellsMap& cells, const ConnectionsMap& conns, int& width, int& height);
    static void writeSizeInJSON(json& j, int width, int height);
};

