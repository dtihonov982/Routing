#include <algorithm>

#include "Circuit.h"
#include "Exception.h"

Point Circuit::getCoordsOfEndpoint(const Endpoint& e) const {
    auto it = cells_.find(e.cellName);
    if (it == cells_.end())
        throw Exception("Can't find ", e.cellName, " in cells");
    auto& cell = it->second;

    double x = cell.getX();
    double y = cell.getY();
    auto& cellType = cell.getType();
    auto& pin = cellType.getPin(e.cellPinName);
    auto pinPos = pin.getPosition();

    // Add cell position and pin position on cell
    x += pinPos.x;
    y += pinPos.y;

    return {x, y};
}

json Circuit::toJSON() const {
    json j;
    std::vector<int> sizeVect{width_, height_};
    j["size"] = sizeVect;

    json tmp;
    for (const auto& [name, cell]: cells_) {
        cell.toJSON(tmp);
    }
    j["cells"] = tmp;

    wires_.toJSON(j);

    return j;
}

std::vector<Point> Circuit::getCoordsOfEndpoints(const std::vector<Endpoint>& eps) const {
    std::vector<Point> result(eps.size());
    std::transform(eps.begin(), eps.end(), result.begin(), 
        [&] (const Endpoint& ep) {
            return getCoordsOfEndpoint(ep);
        }
    );
    return result;
}
