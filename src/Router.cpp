#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

#include "Router.h"
#include "Exception.h"
#include "Point.h"

double getConnLevel(int num);
std::vector<Point> resolveEndpoints(const CellsMap& cells, const std::vector<Endpoint>& eps);
Rect makeVerticalWire(const Point& bottom, double upY);
Rect makeVia(const Point& p);
Wires createWires(std::vector<Point>&& points, int num);

// Create wires that represents given connections and updates height.
Wires Router::route(const CellsMap& cells, const ConnectionsMap& conns, int& width, int& height) {
    int numOfConn = 0;
    Wires result;
    for (auto& [connName, endpoints]: conns) {
        auto points = resolveEndpoints(cells, endpoints);
        auto wires = createWires(std::move(points), numOfConn++);
        result.addWires(wires);
    }
    // There is space above top horizontal wire. But height is integer, so it is need to ceil.
    height = std::ceil(getConnLevel(numOfConn));
    return result;
}

// For each endpoint finds its coordinates (x, y) on the plane
std::vector<Point> resolveEndpoints(const CellsMap& cells, const std::vector<Endpoint>& eps) {
    std::vector<Point> result;
    for (auto& e: eps) {
        // First find cell and its position. 

        auto it = cells.find(e.cellName);
        if (it == cells.end())
            throw Exception("Can not find ", e.cellName, " in cells");
        auto& cell = it->second;

        double x = cell.getX();
        double y = cell.getY();

        // Then find a position of a pin on the cell.

        auto& cellType = cell.getType();
        auto& pin = cellType.getPin(e.cellPinName);
        auto pinPos = pin.getPosition();

        // Add cell position and pin position on cell
        x += pinPos.x;
        y += pinPos.y;

        result.emplace_back(x, y);
    }

    return result;
}

// Create wires that connets given points. Num arguments need to evaluate height of horizontal wire.
Wires createWires(std::vector<Point>&& points, int numOfConn) {
    if (points.size() < 2)
        return Wires{};

    double horizontalWireY = getConnLevel(numOfConn);
    // Sort points to find a width of the horizontal wire.
    std::sort(points.begin(), points.end(),
        [] (const Point& lhs, const Point& rhs) {
            return lhs.x < rhs.x;
        }
    );

    // add horizontal wire

    //   +----+-------------+----+-------------+----+
    //   |Via |    hWire    |    |    hWire    |Via | 
    //   |    |     w1      |    |     w1      |    | 
    //   +----+-------------+----+-------------+----+ < horizontalWireY
    //   |    |             |    |             |    | 
    //   | w0 |             | w0 |             | w0 | 
    //   |    |             |    |             |    | 
    //   |    |             o----+             |    | 
    //   |    |                                o----+ 
    //   o----+                                ^ lastPoint        
    //   ^ firstPoint                           

    auto& firstPoint = *points.begin();
    auto& lastPoint  = *points.rbegin();
    Rect hWire = {firstPoint.x, horizontalWireY,
                  lastPoint.x + WIRE_MIN_WIDTH, 
                  horizontalWireY + WIRE_MIN_WIDTH};
    Wires result;
    result.addWire1(hWire);

    // Create vertical wires and via with horizontal line.

    for (auto& p: points) {
        auto w0 = makeVerticalWire(p, horizontalWireY);
        result.addWire0(w0);

        auto via = makeVia(p.x, horizontalWireY);
        result.addVia(via);
    }

    return result;
}

// Each connection has horizontal line. Height of the line is 'level' of connection.
double getConnLevel(int numOfConn) {
    return CELL_HEIGHT + WIRE_MIN_WIDTH * (1 + 2 * numOfConn);
}

//   +----+ < upY
//   |    |
//   |    |
//     ..  
//   |    |
//   |    |
//   o----+
//   ^ bottom
Rect makeVerticalWire(const Point& bottom, double upY) {
    return {bottom.x, bottom.y, bottom.x + WIRE_MIN_WIDTH, upY};
}

//   +----+ 
//   |    |
//   |    |
//   o----+
//   ^(x, y)
Rect makeVia(double x, double y) {
    return {x, y, x + WIRE_MIN_WIDTH, y + WIRE_MIN_WIDTH};
}

// Write size of an area to json file
void Router::writeSizeInJSON(json& j, int width, int height) {
    std::vector<int> sizeVect{width, height};
    j["size"] = {width, height};
}
