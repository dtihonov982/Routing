#pragma once

#include <string>
#include <unordered_map>

#include "nlohmann/json.hpp"

#include "Rect.h"

using json = nlohmann::json;

class Pin {
public:
    Pin(const std::string& name, const Rect& rect): name_(name), rect_(rect) {}
    std::string getName() { return name_; }
    static std::unordered_map<std::string, Pin> loadFromJSON(const json& j);
private:
    std::string name_;
    Rect rect_;
};
