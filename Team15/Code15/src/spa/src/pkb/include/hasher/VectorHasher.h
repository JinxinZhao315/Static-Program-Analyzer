#include <vector>
#include <string>

struct VectorHasher {
    std::size_t operator()(const std::vector<std::string>& v) const {
        std::size_t seed = v.size();
        for (const auto& str : v) {
            for (const auto& c : str) {
                seed ^= static_cast<size_t>(c) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};