#include "CircuitBuilder.h"
#include "CellsAllocator.h"
#include "Router.h"

Circuit CircuitBuilder::build(CellsMap&& cells) {
    auto [width, height] = CellsAllocator::allocate(cells);
    Circuit circuit(std::move(cells), width, height);
    Router::route(circuit);
    return circuit;
}
