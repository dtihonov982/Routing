#include <algorithm>

#include <vector>

#include "Circuit.h"
#include "Exception.h"

#if 0
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
#endif

json Circuit::toJSON() const {
    json j;
    std::vector<int> sizeVect{width_, height_};
    j["size"] = sizeVect;

    json tmp;
    for (const auto& cell: cells_) {
        cell.toJSON(tmp);
    }
    j["cells"] = tmp;

    wires_.toJSON(j);

    return j;
}

#if 0
std::vector<Point> Circuit::getCoordsOfEndpoints(const std::vector<Endpoint>& eps) const {
    std::vector<Point> result(eps.size());
    std::transform(eps.begin(), eps.end(), result.begin(), 
        [&] (const Endpoint& ep) {
            return getCoordsOfEndpoint(ep);
        }
    );
    return result;
}
#endif


Connections groupByConnName(const std::vector<Endpoint>& endpoints);

Connections Circuit::getConnections() const {
    std::vector<Endpoint> endpoints;
    // Extract all connections with real position on circuit
    for (auto& cell: cells_) {
        auto currEps = cell.getEndpoints();
        endpoints.insert(endpoints.end(), currEps.begin(), currEps.end());
    }
    return groupByConnName(endpoints);
}

Connections groupByConnName(const std::vector<Endpoint>& endpoints) {
    Connections conns;
    for (auto& ep: endpoints) {
        conns[ep.connName].push_back(ep.pinPos);
    }
    return conns;
}

