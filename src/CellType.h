#pragma once

#include <unordered_map>
#include <string>

#include "nlohmann/json.hpp"

#include "Pin.h"

using json = nlohmann::json;

class CellType {
public:
    CellType(const std::string& name, int width, const std::unordered_map<std::string, Pin>& pins)
    : name_(name), width_(width), pins_(pins) {
    }

    static std::unordered_map<std::string, CellType> loadFromJSON(const json& j);

private:
    std::string name_;
    int width_;
    int height_ = 1;
    std::unordered_map<std::string, Pin> pins_;
};
