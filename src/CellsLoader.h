#pragma once

#include <unordered_map>
#include <string>

#include "nlohmann/json.hpp"

#include "Cell.h"

using json = nlohmann::json;

class CellsLoader {
public:
    // Using CellsMap for searching cells while resolving each endpoint in connection
    static Cells fromJSON(const TypesMap& types, const json& j);
};

