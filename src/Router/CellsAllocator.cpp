#include "CellsAllocator.h"

// All cells on the same line on the bottom of the area.
std::pair<int, int> CellsAllocator::allocate(Cells& cells) {
    int currX = 0;
    int currY = 0;
    for (auto& cell: cells) {
        cell.setX(currX);
        cell.setY(currY);
        auto type = cell.getType();
        currX += type.getWidth();
    }
    // Now currX and currY are bottom right corner of an area. 
    // The height of all cells is always 1. Further it changes by Router depends on wires.
    return {currX, 1};
}
