#include "Pin.h"
#include "Exception.h"

PinsMap Pin::fromJSON(const json& j) {
    if (!j.is_object()) {
        throw Exception("Error while parsing pin from json.");
    }
    PinsMap result;
    for (auto& [key, value]: j.items()) {
        auto rect = Rect::loadFromJSON(value);
        Pin pin(key, rect);
        result.insert({key, pin});
    }
    return result;
}
