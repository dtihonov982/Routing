#include <utility>

#include "CellType.h"
#include "Common/Exception.h"

CellType::CellType(const std::string& name, int width, const std::vector<Pin>& pins)
: name_(name), width_(width), pins_(pins) {
}

TypesMap CellType::fromJSON(const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while loading cell type from json.");
    }

    TypesMap result;
    int width;
    std::vector<Pin> pins;
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

// Pins count less than 10. So brute linear search.
const Pin& CellType::getPin(const std::string& name) const {
    for (auto& pin: pins_) {
        if (pin.getName() == name) {
            return pin;
        }
    }
    throw Exception("Can't find pin with name ", name, ".");
}
