#pragma once

#include <string>
#include <unordered_map>

#include "nlohmann/json.hpp"

#include "Rect.h"
#include "Point.h"

using json = nlohmann::json;

class Pin {
public:
    Pin(const std::string& name, const Rect& rect): name_(name), rect_(rect) {}
    std::string getName() const { return name_; }
    static std::vector<Pin> fromJSON(const json& j);
    Point getPosition() const { return {rect_.x0, rect_.y0}; }
private:
    std::string name_;
    Rect rect_;
};

