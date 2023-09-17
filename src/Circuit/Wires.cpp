#include "Wires.h"

void Wires::addWires(const Wires& wires) {
    wires0_.insert(wires0_.end(), wires.wires0_.begin(), wires.wires0_.end());
    wires1_.insert(wires1_.end(), wires.wires1_.begin(), wires.wires1_.end());
    via_.insert(via_.end(), wires.via_.begin(), wires.via_.end());
}

void WireTypeToJSON(const std::string typeName, const std::vector<Rect>& wires, json& j) {
    auto& arr = j[typeName];
    for (auto& r: wires) {
        r.toJSON(arr);
    }
}

void Wires::toJSON(json& j) const {
    WireTypeToJSON("wires0", wires0_, j);
    WireTypeToJSON("wires1", wires1_, j);
    WireTypeToJSON("via", via_, j);
}
