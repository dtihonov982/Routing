#pragma once

#include "Circuit/Cell.h"

class CellsAllocator {
public:
    // Changes x and y of each cell and returns width and height of the area.
    static std::pair<int, int> allocate(Cells& cells);
};

