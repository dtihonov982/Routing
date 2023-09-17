#pragma once

#include <vector>

#include "Endpoint.h"
#include "Cell.h"

class ConnectionsExtractor {
public:
    // Extracts all connections from cells with real position of pins 
    // and groups them by the name of the connection.
    static Connections extract(const std::vector<Cell>& cells);
};
