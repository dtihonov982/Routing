#pragma once

#include "Endpoint.h"
#include "Cell.h"
#include "Circuit.h"

class CircuitBuilder {
public:
    static Circuit build(CellsMap&& cells, const ConnectionsMap& conns);
};

