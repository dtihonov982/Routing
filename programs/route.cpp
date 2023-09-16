// Wire routing program
// Usage: route input_json cells_json output_json
// Author: Dmitrii Tikhonov
// Email: dtihonov982@gmail.com

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "CellsLoader.h"
#include "CellsAllocator.h"
#include "Router.h"
#include "Exception.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) 
try {
    if(argc != 4) {
        std::cerr << "Usage: route input_json cells_json output_json" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream cellsJsonFile(argv[2]);
    if (!cellsJsonFile) {
        std::cerr << "Can't open " << argv[2] << std::endl;
        return EXIT_FAILURE;
    }

    // Loading cells types from json file
    json cellsTypeJson = json::parse(cellsJsonFile);
    auto types = CellType::fromJSON(cellsTypeJson);

    std::ifstream inputJsonFile(argv[1]);
    if (!inputJsonFile) {
        std::cerr << "Can't open " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    json inputJson = json::parse(inputJsonFile);

    // Loading cells and connections between them from file.
    auto [cells, conns] = CellsLoader::fromJSON(types, inputJson);
    // Place cells on an area. Getting width and height of the area.
    auto [width, height] = CellsAllocator::allocate(cells);
    // Creating wires in the area.
    Circuit circuit(std::move(cells), width, height);
    Router::route(circuit, conns);

    std::ofstream outFile(argv[3]);
    if (!outFile) {
        std::cerr << "Can't open " << argv[3] << std::endl;
        return EXIT_FAILURE;
    }

    // Writing results of the program into output file.
    try {
        json out;
        Router::writeSizeInJSON(out, circuit.getWidth(), circuit.getHeight());
        Cell::toJSON(out, circuit.getCells());
        circuit.getWires().toJSON(out);
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
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
}
