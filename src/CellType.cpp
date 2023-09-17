#include <utility>

#include "CellType.h"
#include "Exception.h"

TypesMap CellType::fromJSON(const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while loading cell type from json.");
    }

    TypesMap result;
    int width;
    PinsMap pins;
    for (auto& [typeName, value]: j.items()) {
        if (value.find("width") != value.end()) {
            width = value["width"];
        }
        else {
            throw Exception("No width value in current json object.");
        }

        if (value.find("pins") != value.end()) {
            pins = Pin::fromJSON(value["pins"]);
        }
        else {
            throw Exception("No pins value in current json object.");
        }
        CellType tmp(typeName, width, pins);
        result.emplace(typeName, std::move(tmp));
    }
    return result;
}

const Pin& CellType::getPin(const std::string& name) const {
    auto it = pins_.find(name);
    if (it == pins_.end())
        throw Exception("Can't find pin with name ", name, ".");
    return it->second;
}
