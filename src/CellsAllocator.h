#pragma once

#include "Cell.h"

class CellsAllocator {
public:
    // Changes x and y of each cell and returns width and height of the area.
    static std::pair<int, int> allocateByLadder(CellsMap& cells);
};

