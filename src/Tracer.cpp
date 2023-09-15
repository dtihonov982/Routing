#include "Tracer.h"

double getConnLevel(int num) {
    return CELL_HEIGHT + WIRE_MIN_WIDTH * (1 + 2 * num);
}

Wires Tracer::tracePaths(const CellsMap& cells, const Connections& conns, int& width, int& height) {
    return Wires{};
}

