#pragma once

#include <unordered_map>
#include <string>

#include "nlohmann/json.hpp"

#include "Pin.h"

using json = nlohmann::json;

#define CELL_HEIGHT 1

class CellType;

using TypeInfo = std::unordered_map<std::string, CellType>;

class CellType {
public:
    CellType(const std::string& name, int width, const std::unordered_map<std::string, Pin>& pins)
    : name_(name), width_(width), pins_(pins) {
    }

    static TypeInfo loadFromJSON(const json& j);

    int getWidth() { return width_; }
    int getHeight() { return height_; }

private:
    std::string name_;
    int width_;
    int height_ = CELL_HEIGHT;
    std::unordered_map<std::string, Pin> pins_;
};
