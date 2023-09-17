#pragma once

#include "Cell.h"
#include "Circuit.h"

class CircuitBuilder {
public:
    static Circuit build(Cells&& cells);
};

