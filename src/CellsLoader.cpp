#include "CellsLoader.h"
#include "Exception.h"

std::pair<CellsMap, Connections> CellsLoader::loadFromJSON(const TypeInfo& types, const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while loading cells from json.");
    }

    CellsMap cells;
    Connections conns;
    if (j.find("cells") == j.end()) {
        throw Exception("No 'cells' value in json file.");
    }
    auto& obj = j["cells"];
    std::string typeName;
    for (auto& [cellName, cellInfo]: obj.items()) {
        if (cellInfo.find("type") != cellInfo.end()) {
            typeName = cellInfo["type"];
        }
        else {
            throw Exception("No type value in current json object.");
        }
    }

    return {cells, conns};


}
