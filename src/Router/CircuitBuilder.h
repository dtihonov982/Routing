#pragma once

#include "Circuit/Cell.h"
#include "Circuit/Circuit.h"

class CircuitBuilder {
public:
    static Circuit build(Cells&& cells);
};

