#pragma once

#include "Circuit.h"

class CircuitBuilder {
public:
    // Changes x and y of each cell and returns width and height of the area.
    static std::pair<int, int> allocate(CellsMap& cells);
    static Circuit build(CellsMap&& cells, const ConnectionsMap& conns);
};

