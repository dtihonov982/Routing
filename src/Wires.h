#pragma once

#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Rect.h"

#define WIRE_MIN_WIDTH 0.1

#if 0
class Wire {
public:
    enum Type { Wire0, Via, Wire1 };

    Wire(Type type, const Rect& rect): type_(type), rect_(rect) {}
    Wire() {}
    void setRect(const Rect& rect) { rect_ = rect; }
    void setType(Type type) { type_ = type; }
    
private:
    Type type_;
    Rect rect_;
};
#endif

class Wires {
public:
    void addInWires0(const Rect& rect) {
        wires0_.push_back(rect);
    }

    void addInWires1(const Rect& rect) {
        wires1_.push_back(rect);
    }

    void addInVia(const Rect& rect) {
        via_.push_back(rect);
    }

private:
    std::vector<Rect> wires0_;
    std::vector<Rect> wires1_;
    std::vector<Rect> via_;
};
