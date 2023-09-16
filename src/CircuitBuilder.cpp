#include "CircuitBuilder.h"
#include "CellsAllocator.h"
#include "Router.h"

Circuit CircuitBuilder::build(CellsMap&& cells, const ConnectionsMap& conns) {
    auto [width, height] = CellsAllocator::allocate(cells);
    Circuit circuit(std::move(cells), width, height);
    Router::route(circuit, conns);
    return circuit;
}
