#pragma once

#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Wires.h"
#include "Cell.h"
#include "Endpoint.h"

class Tracer {
public:
    static Wires tracePaths(const CellsMap& cells, const Connections& conns, int& width, int& height);
    static void writeSizeInJSON(json& j, int width, int height);
};

