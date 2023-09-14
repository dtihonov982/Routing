#include "CellType.h"
#include "Exception.h"

std::unordered_map<std::string, CellType> CellType::loadFromJSON(const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while cell type from json.");
    }

    std::unordered_map<std::string, CellType> result;
    int width;
    std::unordered_map<std::string, Pin> pins;
    for (auto& [key, value]: j.items()) {
        if (value.find("width") != value.end()) {
            width = value["width"];
        }
        else {
            throw Exception("No width value in current json object.");
        }

        if (value.find("pins") != value.end()) {
            pins = Pin::loadFromJSON(value["pins"]);
        }
        else {
            throw Exception("No pins value in current json object.");
        }
        CellType tmp(key, width, pins);
        result.insert({key, tmp});

    }
    return result;
}
