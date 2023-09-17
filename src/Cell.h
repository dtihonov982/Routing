#pragma once

#include <string>
#include <unordered_map>

#include "CellType.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class Cell;

using CellsMap = std::unordered_map<std::string, Cell>;
using Cells = std::vector<Cell>;

class Cell {
public:
    Cell(const std::string& name, const CellType& type)
    : name_(name), type_(type) {
    }

    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }

    int getX() const { return x_; }
    int getY() const { return y_; }

    const CellType& getType() const { return type_; }

    void toJSON(json& j) const;
    
    static Cell createCellWithType(const std::string& cellName, const TypesMap& types, const std::string& typeName);
    static void toJSON(json& j, const CellsMap& cells);

    void setConnections(const std::unordered_map<std::string, std::string>& conns) {
        conns_ = conns;
    }

private:
    std::string name_;
    CellType type_;
    int x_ = 0;
    int y_ = 0;
    std::unordered_map<std::string, std::string> conns_;
};

