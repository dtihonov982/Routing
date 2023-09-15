#include "CellsLoader.h"
#include "Exception.h"

void addConnections(Connections& info, const std::string& cellName, const json& j);

Cell createCell(const std::string& cellName, const TypesMap& types, const std::string& typeName);

std::pair<CellsMap, Connections> CellsLoader::fromJSON(const TypesMap& types, const json& j) {
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

// Connections stores apart from each cell. There is no need to know about cell while routing connections.
// But it is need to know about each pin position while routing. In this solution each connection stores name of cell and pin.
// Router finds related cell and pin by his name and evaluates pin coords.
void addConnections(Connections& info, const std::string& cellName, const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while loading information about connections.");
    }

    for (auto& [pinName, connName]: j.items()) {
        Endpoint ep{cellName, pinName};
        info[connName].push_back(ep);
    }
}

// Create concrete cell with name and type.
Cell createCell(const std::string& cellName, const TypesMap& types, const std::string& typeName) {
    auto it = types.find(typeName);
    if (it == types.end()) {
        throw Exception("Bad cell type ", typeName);
    }
    const CellType& type = it->second;
    return Cell(cellName, type);
}

