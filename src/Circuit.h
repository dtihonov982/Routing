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
    Circuit(Cells&& cells, int width, int height)
    : cells_(std::move(cells)) 
    , width_(width)
    , height_(height) {
    }

    int getWidth() { return width_; }
    int getHeight() { return height_; }
    void setWidth(int width) { width_ = width; }
    void setHeight(int height) { height_ = height; }

    const Cells& getCells() { return cells_; }

    Wires& getWires() { return wires_; }
    const Wires& getWires() const { return wires_; }
    void addWires(const Wires& wires) { wires_.addWires(wires); }
    void setWires(Wires&& wires) { wires_ = std::move(wires); }

    Connections getConnections() const;

#if 0
    Point getCoordsOfEndpoint(const Endpoint& e) const;
    std::vector<Point> getCoordsOfEndpoints(const std::vector<Endpoint>& eps) const;
#endif

    json toJSON() const;
private:
    Cells cells_;
    Wires wires_;
    int width_;
    int height_;
};
