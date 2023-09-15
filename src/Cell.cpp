#include "Cell.h"

#include <string>

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
