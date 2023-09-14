#pragma once

#include <string>

struct Connection {
    std::string name;
    std::string first;
    std::string second;
};

using Connection = std::vector<Connection>;
