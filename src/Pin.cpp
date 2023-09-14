#include "Pin.h"
#include "Exception.h"

std::unordered_map<std::string, Pin> Pin::loadFromJSON(const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while parsing pin from json.");
    }
    std::unordered_map<std::string, Pin> result;
    for (auto& [key, value]: j.items()) {
        auto rect = Rect::loadFromJSON(value);
        Pin pin(key, rect);
        result.insert({key, pin});
    }
    return result;
}
