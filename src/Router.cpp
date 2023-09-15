#include <vector>
#include <algorithm>
#include <cmath>

#include "Router.h"
#include "Exception.h"
#include "Point.h"

double getConnLevel(int num) {
    return CELL_HEIGHT + WIRE_MIN_WIDTH * (1 + 2 * num);
}

std::vector<Point> resolveEndpoints(const CellsMap& cells, const std::vector<Endpoint>& eps) {
    std::vector<Point> result;
    // First find cell and its position. Then find a position of a pin on the cell.
    for (auto& e: eps) {
        auto it = cells.find(e.cellName);
        if (it == cells.end())
            throw Exception("Can not find ", e.cellName, " in cells");
        auto& cell = it->second;

        double x = cell.getX();
        double y = cell.getY();

        auto& cellType = cell.getType();
        auto& pin = cellType.getPin(e.cellPinName);
        auto pinPos = pin.getPosition();

        x += pinPos.x;
        y += pinPos.y;

        result.push_back({x, y});
    }

    return result;
}

Rect makeVerticalWire(const Point& bottom, double upY) {
    return {bottom.x, bottom.y, bottom.x + WIRE_MIN_WIDTH, upY};
}

Rect makeVia(const Point& p) {
    return {p.x, p.y, p.x + WIRE_MIN_WIDTH, p.y + WIRE_MIN_WIDTH};
}

Wires createWires(std::vector<Point>& points, int num) {
    if (points.size() < 2)
        return Wires{};

    double horizontalWireY = getConnLevel(num);
    std::sort(points.begin(), points.end(),
        [] (const Point& lhs, const Point& rhs) {
            return lhs.x < rhs.x;
        }
    );

    auto& firstPoint = points[0];
    auto& lastPoint = *points.rbegin();
    Rect hWire = {firstPoint.x, horizontalWireY,
                  lastPoint.x + WIRE_MIN_WIDTH, horizontalWireY + WIRE_MIN_WIDTH};

    Wires result;
    result.addWire1(hWire);

    // Create vertical wires and via with horizontal line.
    for (auto& p: points) {
        Rect w0 = makeVerticalWire(p, horizontalWireY);
        Rect via = makeVia({p.x, horizontalWireY});
        result.addWire0(w0);
        result.addVia(via);
    }

    return result;
}


Wires Router::route(const CellsMap& cells, const Connections& conns, int& width, int& height) {
    int numOfConn = 0;
    Wires result;
    for (auto& [connName, endpoints]: conns) {
        auto points = resolveEndpoints(cells, endpoints);
        auto wires = createWires(points, numOfConn++);
        result.addWires(wires);
    }
    height = std::ceil(getConnLevel(numOfConn));
    return result;
}

void Router::writeSizeInJSON(json& j, int width, int height) {
    std::vector<int> sizeVect{width, height};
    j["size"] = sizeVect;
}
