#include "Cell.h"
#include "Exception.h"

#include <string>

// Create concrete cell with name and type.
Cell Cell::createCellWithType(const std::string& cellName, const TypesMap& types, const std::string& typeName) {
    auto it = types.find(typeName);
    if (it == types.end()) {
        throw Exception("Can't find cell type with name ", typeName);
    }
    const CellType& type = it->second;
    return Cell(cellName, type);
}

void Cell::toJSON(json& j) const {
    auto& arr = j[name_];
    arr.push_back(type_.getName());
    arr.push_back(x_);
    arr.push_back(y_);
}

void Cell::toJSON(json& j, const CellsMap& cells) {
    json tmp;
    for (const auto& [name, cell]: cells) {
        cell.toJSON(tmp);
    }
    j["cells"] = tmp;

}

std::vector<Endpoint> Cell::getEndpoints() const {
    std::vector<Endpoint> result;

    for (const auto& [pinName, connName]: conns_) {
        auto& pin = type_.getPin(pinName);
        Point pinRelativePos = pin.getPosition();
        Point pinAbsolutePos {x_ + pinRelativePos.x, y_ + pinRelativePos.y};
        result.push_back({connName, pinAbsolutePos});
    }

    return result;
}
