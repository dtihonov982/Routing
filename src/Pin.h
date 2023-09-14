#pragma once

#include <string>

#include "Rect.h"

class Pin {
public:
    Pin(const std::string& name, const Rect& rect): name_(name), rect_(rect) {}
    std::string getName() { return name_; }
private:
    std::string name_;
    Rect rect_;
};
