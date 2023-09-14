#pragma once

#include <unordered_map>
#include <string>

#include "nlohmann/json.hpp"

#include "Cell.h"
#include "Endpoint.h"

using json = nlohmann::json;

class CellsLoader {
public:
    static std::pair<CellsMap, Connections> loadFromJSON(const TypeInfo& types, const json& j);
};

