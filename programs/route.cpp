// Wire routing program
// Usage: route input_json cells_json output_json
// Author: Dmitrii Tikhonov
// Email: dtihonov982@gmail.com

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "Common/Exception.h"
#include "Circuit/CellType.h"
#include "Router/CircuitBuilder.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) 
try {
    if(argc != 4) {
        std::cerr << "Usage: route input_json cells_json output_json" << std::endl;
        return EXIT_FAILURE;
    }

    // Open json file with cell types
    std::ifstream cellsJsonFile(argv[2]);
    if (!cellsJsonFile) {
        std::cerr << "Can't open " << argv[2] << std::endl;
        return EXIT_FAILURE;
    }

    // Loading cells types from json file
    json cellsTypeJson = json::parse(cellsJsonFile);
    TypesMap types = CellType::fromJSON(cellsTypeJson);

    // Open file with cells and connections
    std::ifstream inputJsonFile(argv[1]);
    if (!inputJsonFile) {
        std::cerr << "Can't open " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    // Loading cells and connections between them from file.
    json inputJson = json::parse(inputJsonFile);
    auto cells = Cell::fromJSON(types, inputJson);

    // Allocating cells on circuit, find connections, routing wires.
    Circuit circuit = CircuitBuilder::build(std::move(cells));

    // Open output file.
    std::ofstream outFile(argv[3]);
    if (!outFile) {
        std::cerr << "Can't open " << argv[3] << std::endl;
        return EXIT_FAILURE;
    }

    // Dump information about circuit (size, allocation, wires) into the file.
    json circuitDump;
    circuit.toJSON(circuitDump);
    outFile << circuitDump;

    return EXIT_SUCCESS;
}
catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
}


