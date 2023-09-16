#pragma once

#include "nlohmann/json.hpp"

#include "Cell.h"
#include "Endpoint.h"
#include "Wires.h"
#include "Point.h"

using json = nlohmann::json;

class Circuit {
public:
    Circuit() {}
    Circuit(CellsMap&& cells, int width, int height)
    : cells_(std::move(cells)) 
    , width_(width)
    , height_(height) {
    }

    int getWidth() { return width_; }
    int getHeight() { return height_; }
    void setWidth(int width) { width_ = width; }
    void setHeight(int height) { height_ = height; }

    CellsMap& getCells() { return cells_; }
    const CellsMap& getCells() const { return cells_; }
    void addCell(const std::string& name, const Cell& cell) {
        cells_.emplace(name, cell);
    }

    Wires& getWires() { return wires_; }
    const Wires& getWires() const { return wires_; }
    void addWires(const Wires& wires) { wires_.addWires(wires); }

    Point getCoordsOfEndpoint(const Endpoint& e) const;

    json toJSON() const;
private:
    CellsMap cells_;
    Wires wires_;
    int width_;
    int height_;
};
