#pragma once

#include <string>

// Endpoint is a pin of certian cell
struct Endpoint {
    std::string cellName;
    std::string cellPinName;
};

using Connections = std::unordered_map<std::string, std::vector<Endpoint>>;
