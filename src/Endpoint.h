#pragma once

#include <string>

// Endpoint is a pin of certian cell
struct Endpoint {
    Endpoint() {}
    Endpoint(const std::string& cellName_, const std::string& cellPinName_):
    cellName(cellName_), cellPinName(cellPinName_) {}

    std::string cellName;
    std::string cellPinName;
};

// Key is connection name, as example "b3". Use vector because may be many pins in each connection.
using ConnectionsMap = std::unordered_map<std::string, std::vector<Endpoint>>;
