#include "Pin.h"
#include "Exception.h"

std::vector<Pin> Pin::fromJSON(const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while parsing pin from json.");
    }
    std::vector<Pin> result;
    for (auto& [name, value]: j.items()) {
        auto rect = Rect::loadFromJSON(value);
        result.push_back( Pin(name, rect) );
    }
    return result;
}
