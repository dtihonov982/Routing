#include <fstream>
#include <iostream>

#include "Pin.h"
#include "Rect.h"
#include "CellType.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
    if(argc != 2)
    {
        std::cerr <<
            "Usage: nlohmann <filename> <filename>"
            << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream f(argv[1]);
    json data = json::parse(f);

    auto pins = CellType::loadFromJSON(data);

    return 0;
}
