#pragma once

#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Rect.h"

#define WIRE_MIN_WIDTH 0.1

class Wires {
public:
    void addWire0(const Rect& rect) {
        wires0_.push_back(rect);
    }

    void addWire1(const Rect& rect) {
        wires1_.push_back(rect);
    }

    void addVia(const Rect& rect) {
        via_.push_back(rect);
    }

    void addWires(const Wires& wires);

    void toJSON(json& j) const;

private:
    std::vector<Rect> wires0_;
    std::vector<Rect> wires1_;
    std::vector<Rect> via_;
};
