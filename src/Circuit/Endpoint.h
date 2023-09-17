#pragma once

#include <string>
#include <unordered_map>

#include "Common/Point.h"

// Endpoint is a pin of certain cell on circuit
struct Endpoint {
    std::string connName;
    Point pinPos;
};

// Key is connection name, as example "b3". Use vector because may be many pins in each connection.
using Connections = std::unordered_map<std::string, std::vector<Point>>;
