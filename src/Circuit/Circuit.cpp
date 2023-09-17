#include <vector>

#include "Circuit.h"
#include "Common/Exception.h"

void Circuit::toJSON(json& j) const {
    std::vector<int> sizeVect{width_, height_};
    j["size"] = sizeVect;

    json tmp;
    for (const auto& cell: cells_) {
        cell.toJSON(tmp);
    }
    j["cells"] = tmp;

    wires_.toJSON(j);

}

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

