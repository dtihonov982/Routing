#pragma once

#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Circuit.h"

class Router {
public:
    static void route(Circuit& circuit);
};

