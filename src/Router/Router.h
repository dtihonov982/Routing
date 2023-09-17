#pragma once

#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Circuit/Circuit.h"

class Router {
public:
    // Create wires on circuit and update a size of circuit.
    static void route(Circuit& circuit);
};

