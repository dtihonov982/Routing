#pragma once

#include "Circuit.h"

class CircuitBuilder {
public:
    static Circuit build(CellsMap&& cells, const ConnectionsMap& conns);
};

