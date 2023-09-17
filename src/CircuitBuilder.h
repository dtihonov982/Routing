#pragma once

#include "Cell.h"

class CircuitBuilder {
public:
    static Circuit build(CellsMap&& cells);
};

