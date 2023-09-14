#pragma once

#include <string>
#include <unordered_map>

#include "CellType.h"

class Cell {
public:
    Cell(const std::string& name, const CellType& type)
    : name_(name), type_(type) {
    }

    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }

private:
    std::string name_;
    CellType type_;
    double x_;
    double y_;
};

using CellsMap = std::unordered_map<std::string, Cell>;

