#pragma once

#include <string>
#include <unordered_map>

#include "Point.h"

#if 0
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
#endif

struct Endpoint {
    std::string connName;
    Point pinPos;
};

using Connections = std::unordered_map<std::string, std::vector<Point>>;
