#include "ConnectionsExtractor.h"

Connections groupByConnName(const std::vector<Endpoint>& endpoints) {
    Connections conns;
    for (auto& ep: endpoints) {
        conns[ep.connName].push_back(ep.pinPos);
    }
    return conns;
}

Connections ConnectionsExtractor::extract(const std::vector<Cell>& cells) {
    std::vector<Endpoint> endpoints;
    // Extract all connections with real position on circuit
    for (auto& cell: cells) {
        auto currEps = cell.getEndpoints();
        endpoints.insert(endpoints.end(), currEps.begin(), currEps.end());
    }
    return groupByConnName(endpoints);
}
