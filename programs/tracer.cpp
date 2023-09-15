#include <fstream>
#include <iostream>
#include <stdexcept>

#include "CellsLoader.h"
#include "CellsAllocator.h"
#include "Tracer.h"
#include "Exception.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) try {
    if(argc != 4)
    {
        std::cerr << "Usage: tracer input_json cells_json output_json" << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream cellsJsonFile(argv[2]);
    if (!cellsJsonFile) {
        std::cerr << "Can not open " << argv[2] << std::endl;
        return EXIT_FAILURE;
    }

    json cellsTypeJson = json::parse(cellsJsonFile);
    auto types = CellType::loadFromJSON(cellsTypeJson);

    std::ifstream inputJsonFile(argv[1]);
    if (!inputJsonFile) {
        std::cerr << "Can not open " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }
    json inputJson = json::parse(inputJsonFile);

    auto [cells, conns] = CellsLoader::loadFromJSON(types, inputJson);
    auto [width, height] = CellsAllocator::allocate(cells);
    auto wires = Tracer::tracePaths(cells, conns, width, height);

    std::ofstream outFile(argv[3]);
    if (!outFile) {
        std::cerr << "Can not open " << argv[3] << std::endl;
        return EXIT_FAILURE;
    }

    try {
        json out;
        Tracer::writeSizeInJSON(out, width, height);
        Cell::toJSON(out, cells);
        wires.toJSON(out);
        outFile << out;
    }
    catch (const Exception& e) {
        std::cerr << "Error while saving results in " << argv[3] << ": "
            << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
catch (const std::exception& e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return EXIT_FAILURE;
}
