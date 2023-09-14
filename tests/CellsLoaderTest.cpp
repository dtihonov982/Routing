#include <fstream>
#include <iostream>

#include "Pin.h"
#include "Rect.h"
#include "CellType.h"
#include "CellsLoader.h"

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
    auto p = CellsLoader::loadFromJSON(types, data2);

    return 0;
}
