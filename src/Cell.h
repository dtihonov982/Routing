#pragma once

#include <string>
#include <unordered_map>

#include "CellType.h"

class Cell {
public:
    Cell(const std::string& name, const CellType& type)
    : name_(name), type_(type) {
    }

    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }

    const CellType& getType() { return type_; }

private:
    std::string name_;
    CellType type_;
    int x_ = 0;
    int y_ = 0;
};

using CellsMap = std::unordered_map<std::string, Cell>;

