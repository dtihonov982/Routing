#include <utility>

#include "CellsLoader.h"
#include "Exception.h"

void addConnections(ConnectionsMap& info, const std::string& cellName, const json& j);
void parseConnectionsObject(const json& j, const std::string& cellName, ConnectionsMap& conns);
std::string getValueOfTypeObject(const json& j);

std::pair<CellsMap, ConnectionsMap> CellsLoader::fromJSON(const TypesMap& types, const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while loading cells from json.");
    }

    if (j.find("cells") == j.end()) {
        throw Exception("No 'cells' value in json file.");
    }
    auto& obj = j["cells"];

    CellsMap cells;
    ConnectionsMap conns;
    std::string typeName;
    for (auto& [cellName, cellInfo]: obj.items()) {
        auto typeName = getValueOfTypeObject(cellInfo);
        auto cell = Cell::createCellWithType(cellName, types, typeName);
        cells.emplace(cellName, std::move(cell));

        parseConnectionsObject(cellInfo, cellName, conns);
    }

    return {cells, conns};
}

std::string getValueOfTypeObject(const json& j) {
    if (j.find("type") != j.end()) {
        return j["type"];
    }
    else {
        throw Exception("No 'type' value in current json object.");
    }
}

// Connections stores apart from each cell. There is no need to know about cell while routing connections.
// But it is need to know about each pin position while routing. In this solution each connection stores name of cell and pin.
// Router finds related cell and pin by his name and evaluates pin coordinates.
void addConnections(ConnectionsMap& connMap, const std::string& cellName, const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while loading information about connections.");
    }

    //  from 
    //      cellName: [ pinName: connName, ...]
    //  to 
    //      connName: [ [cellName, pinName], ...]

    for (auto& [pinName, connName]: j.items()) {
        auto& endpoints = connMap[connName];
        endpoints.emplace_back(cellName, pinName);
    }
}

void parseConnectionsObject(const json& j, const std::string& cellName, ConnectionsMap& conns) {
    if (j.find("connections") != j.end()) {
        auto& connEntry = j["connections"];
        addConnections(conns, cellName, connEntry);
    }
    else {
        throw Exception("No 'connections' value in current json object.");
    }
}

