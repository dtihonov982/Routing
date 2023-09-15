#include <fstream>
#include <iostream>

#include "Pin.h"
#include "Rect.h"
#include "CellType.h"
#include "CellsLoader.h"
#include "CellsAllocator.h"
#include "Tracer.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
    if(argc != 3)
    {
        std::cerr <<
            "Usage: nlohmann <filename> <filename>"
            << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream f(argv[1]);
    json data = json::parse(f);

    auto types = CellType::loadFromJSON(data);

    std::ifstream f2(argv[2]);
    json data2 = json::parse(f2);

    auto [cells, conns] = CellsLoader::loadFromJSON(types, data2);

    auto [width, height] = CellsAllocator::allocate(cells);

    auto wires = Tracer::tracePaths(cells, conns, width, height);

    std::ofstream outFile("output.json");
    json out;
    Tracer::writeSizeInJSON(out, width, height);
    Cell::toJSON(out, cells);
    wires.toJSON(out);

    outFile << out;

    return 0;
}
