#pragma once

#include <unordered_map>
#include <string>

#include "nlohmann/json.hpp"

#include "Pin.h"

#define CELL_HEIGHT 1

using json = nlohmann::json;

class CellType;
using TypesMap = std::unordered_map<std::string, CellType>;

class CellType {
public:
    CellType(const std::string& name, int width, const std::vector<Pin>& pins);

    // Using TypesMap instead vector for fast searching a type while loading cells in CellsLoader
    static TypesMap fromJSON(const json& j);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    std::string getName() const { return name_; }

    const Pin& getPin(const std::string& name) const;
private:
    std::string name_;
    int width_;
    int height_ = CELL_HEIGHT;
    // The number of pins less than 10. So there is no need to use unordered_map.
    // It is simpler and may be faster to use linear search through vector.
    std::vector<Pin> pins_;
};
