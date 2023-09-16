// Wire routing program
// Usage: route input_json cells_json output_json
// Author: Dmitrii Tikhonov
// Email: dtihonov982@gmail.com

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "Exception.h"
#include "CellType.h"
#include "CellsLoader.h"
#include "CircuitBuilder.h"

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
    TypesMap types;
    try {
        types = CellType::fromJSON(cellsTypeJson);
    }
    catch (const Exception& e) {
        std::cerr << "Can't load information about cells types: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream inputJsonFile(argv[1]);
    if (!inputJsonFile) {
        std::cerr << "Can't open " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    json inputJson = json::parse(inputJsonFile);

    // Loading cells and connections between them from file.
    auto [cells, conns] = CellsLoader::fromJSON(types, inputJson);

    Circuit circuit;
    try {
        circuit = CircuitBuilder::build(std::move(cells), conns);
    }
    catch (const Exception& e) {
        std::cerr << "Can't build circuit: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::ofstream outFile(argv[3]);
    if (!outFile) {
        std::cerr << "Can't open " << argv[3] << std::endl;
        return EXIT_FAILURE;
    }

    // Writing results of the program into output file.
    try {
        outFile << circuit.toJSON();
    }
    catch (const Exception& e) {
        std::cerr << "Error while saving circuit in " << argv[3] << ": "
            << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
}
