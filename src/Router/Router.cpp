#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

#include "Router.h"
#include "Common/Exception.h"
#include "Common/Point.h"
#include "Circuit/Wires.h"

Wires createWires(std::vector<Point>&& points, int num);
double getConnLevel(int num);
Rect makeVerticalWire(const Point& bottom, double upY);
Rect makeVia(double x, double y);

void Router::route(Circuit& circuit) {
    Connections conns = circuit.getConnections();
    int numOfConnection = 0;
    Wires wires;
    for (auto& [name, points]: conns) {
        Wires currentWires = createWires(std::move(points), numOfConnection++);
        wires.addWires(currentWires);
    }
    circuit.setWires(std::move(wires));
    // There is space < 1.0 above top horizontal wire. But height is integer, so it is need to ceil.
    int height = std::ceil(getConnLevel(numOfConnection));
    circuit.setHeight(height);
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

    //   add horizontal wire

    //   +----+-------------+----+-------------+----+
    //   |Via |    hWire    |    |    hWire    |Via | 
    //   |    |     w0      |    |     w0      |    | 
    //   +----+-------------+----+-------------+----+ < horizontalWireY
    //   |    |             |    |             |    | 
    //   | w1 |             | w1 |             | w1 | 
    //   |    |             |    |             |    | 
    //   |    |             +----+             |    | 
    //   |    |             |Via |             +----+ 
    //   +----+             |    |             |Via | 
    //   |Via |             o----+             |    | 
    //   |    |                                o----+ 
    //   o----+                                ^ lastPoint        
    //   ^ firstPoint                           

    auto& firstPoint = *points.begin();
    auto& lastPoint  = *points.rbegin();
    Rect hWire = {firstPoint.x, horizontalWireY,
                  lastPoint.x + WIRE_MIN_WIDTH, 
                  horizontalWireY + WIRE_MIN_WIDTH};
    Wires result;
    result.addWire0(hWire);

    // Create vertical wires and via with horizontal line and pins

    for (auto& p: points) {
        auto w1 = makeVerticalWire(p, horizontalWireY + WIRE_MIN_WIDTH);
        result.addWire1(w1);

        auto viaWithHor = makeVia(p.x, horizontalWireY);
        result.addVia(viaWithHor);
        auto viaWithPin = makeVia(p.x, p.y);
        result.addVia(viaWithPin);
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
