#include <fstream>
#include <iostream>

#include "Pin.h"
#include "Rect.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
    if(argc != 2)
    {
        std::cerr <<
            "Usage: nlohmann <filename>"
            << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream f(argv[1]);
    json data = json::parse(f);

    std::cout << data.is_object() << std::endl;
    auto pins = Pin::loadFromJSON(data);

    return 0;
}
