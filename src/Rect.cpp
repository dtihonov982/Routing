#include "Rect.h"
#include "Exception.h"

Rect Rect::loadFromJSON(const json& j) {
    if (!j.is_array()) {
        throw Exception("Error while parsing rectangle from json.");
    }
    auto it = j.begin();
    Rect rect;
    rect.x0 = *it++;
    rect.y0 = *it++;
    rect.x1 = *it++;
    rect.y1 = *it++;
    return rect;
}
