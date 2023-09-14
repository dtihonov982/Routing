#pragma once

#include <vector>
#include <string>

class Cell {
public:
    Cell(const std::string& name, const std::vector<Pin>& pins)
    : name_(name), pins_(pins) {
    }


private:
    std::string name_;
    std::vector<Pin> pins_;
};
