#pragma once

#include <string>
#include <vector>

struct VectorHasher {
    std::size_t operator()(std::vector<std::string> vec) const {
        std::size_t seed = vec.size();
        for (auto s : vec) {
            seed ^= std::stoi(s) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};