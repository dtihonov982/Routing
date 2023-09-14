#pragma once

#include "nlohmann/json.hpp"
using json = nlohmann::json;

struct Rect {
    double x0;
    double y0;
    double x1;
    double y1;

    static Rect loadFromJSON(const json& j);
};
