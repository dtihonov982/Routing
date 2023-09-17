#include <utility>

#include "CellsLoader.h"
#include "Exception.h"

std::string getValueOfTypeObject(const json& j);

Cells CellsLoader::fromJSON(const TypesMap& types, const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while loading cells from json.");
    }

    if (j.find("cells") == j.end()) {
        throw Exception("No 'cells' value in json file.");
    }
    auto& obj = j["cells"];

    Cells cells;
    std::string typeName;
    for (auto& [cellName, cellInfo]: obj.items()) {
        auto typeName = getValueOfTypeObject(cellInfo);
        auto cell = Cell::createCellWithType(cellName, types, typeName);
        cell.setConnections(cellInfo["connections"]);
        cells.push_back(std::move(cell));
    }

    return cells;
}

std::string getValueOfTypeObject(const json& j) {
    if (j.find("type") != j.end()) {
        return j["type"];
    }
    else {
        throw Exception("No 'type' value in current json object.");
    }
}
