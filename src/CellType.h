#pragma once

#include <unordered_map>
#include <string>

#include "nlohmann/json.hpp"

#include "Pin.h"

using json = nlohmann::json;

#define CELL_HEIGHT 1

class CellType;
using TypesMap = std::unordered_map<std::string, CellType>;

class CellType {
public:
    CellType(const std::string& name, int width, const PinsMap& pins)
    : name_(name), width_(width), pins_(pins) {
    }

    // Using TypesMap instead vector for fast searching a type while loading cells in CellsLoader
    static TypesMap fromJSON(const json& j);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    std::string getName() const { return name_; }

    const Pin& getPin(const std::string& name) const;
private:
    std::string name_;
    int width_;
    int height_ = CELL_HEIGHT;
    PinsMap pins_;
};
