#include "CellsAllocator.h"

std::pair<int, int> CellsAllocator::allocateByLadder(CellsMap& cells) {
    const int xBorder = 1;
    const int yBorder = 1;
    int currX = xBorder;
    int currY = yBorder;
    for (auto& [name, cell]: cells) {
        cell.setX(currX);
        cell.setY(currY);
        auto type = cell.getType();
        currX += type.getWidth();
        currY += type.getHeight();
    }
    // Now currX and currY are top right corner of an area. And they are width and height.
    return {currX, currY};
}
