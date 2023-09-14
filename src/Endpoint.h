#pragma once

#include <string>

struct Endpoint {
    std::string cellName;
    std::string cellPinName;
};

using Connections = std::unordered_map<std::string, std::vector<Endpoint>>;
