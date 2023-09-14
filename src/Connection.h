#pragma once

#include <string>

struct Endpoint {
    std::string cellName;
    std::string cellPinName;
};

struct Connection {
    std::string name;
    std::string firstCell;
    std::string firstPin;
    std::string secondCell;
    std::string secondPin;
};

using Connections = std::vector<Connection>;
