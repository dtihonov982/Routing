#include "CellsLoader.h"
#include "Exception.h"

void addConnections(Connections& info, const std::string& cellName, const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while loading information about connections.");
    }

    for (auto& [pinName, connName]: j.items()) {
        Endpoint ep{cellName, pinName};
        info[connName].push_back(ep);
    }
}

Cell createCell(const std::string& cellName, const TypeInfo& types, const std::string& typeName) {
    auto it = types.find(typeName);
    if (it == types.end()) {
        throw Exception("Bad cell type ", typeName);
    }
    const CellType& type = it->second;
    return Cell(cellName, type);
}

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
            auto cell = createCell(cellName, types, typeName);
            cells.insert({cellName, cell});
        }
        else {
            throw Exception("No type value in current json object.");
        }
        if (cellInfo.find("connections") != cellInfo.end()) {
            auto& connEntry = cellInfo["connections"];
            addConnections(conns, cellName, connEntry);
        }
        else {
            throw Exception("No 'connections' value in current json object.");
        }
    }

    return {cells, conns};
}

