#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

class Template {
public:
    Template(const std::string& temp, const std::vector<std::string>& keys)
    : template_(temp), keys_(keys) {
    }

    std::string replace(const std::unordered_map<std::string, std::string>& values) {
        std::string str = template_;
        for (auto& [key, value]: values) {
            str = replaceAll(str, key, value);
        }
        return str;
    }

    static std::string  replaceAll(std::string origin, const std::string& key, const std::string& value) {
        std::string::size_type n = 0;
        size_t keySize = key.size();
        for (;;) {
            n = origin.find(key, n);
            if (n == std::string::npos) 
                break;
            origin.replace(n, keySize, value);
            n += value.size() + 1;
        }

        return origin;
    }
private:
    std::string template_;
    std::vector<std::string> keys_;
};

void addTestData(std::ofstream& os, Template& t, size_t count) {
    size_t numFirst = 0;
    size_t numSecond = 1;
    size_t numConn = 0;
    for (size_t i = 0; i < count; ) {
        os << t.replace({ {"CELL_NAME_FIRST", std::to_string(numFirst)},
                          {"CELL_NAME_SECOND", std::to_string(numSecond)},
                          {"CONN_NAME", std::to_string(numConn)}
                        });
        ++i;
        if (i < count) {
            os << ",\n";
        }
        else {
            os << "\n";
            break;
        }
        numFirst = numSecond + 1;
        numSecond = numFirst + 1;
        numConn++;
    }
}

int main(int argc, char** argv) {
    if (argc != 3)
        return 1;
    std::ofstream out{argv[1]};
    out << R"({
    "cells": {)";

    std::string tmpStr = R"(
        "CELL_NAME_FIRST": {
            "type": "$and",
            "connections": {
                "B": "CONN_NAME"
            }
        },
        "CELL_NAME_SECOND": {
            "type": "$not",
            "connections": {
                "A": "CONN_NAME"
            }
        })";

    Template temp(tmpStr, {"CELL_NAME_FIRST", "CELL_NAME_SECOND", "CONN_NAME"});
    addTestData(out, temp, std::stoi(argv[2]));

    out << R"(
    }
})";

    return 0;

}
