#ifndef VECTOR_HASH_H
#define VECTOR_HASH_H

#include <glm/glm.hpp>

struct VectorXZ {
    int x, z;
    VectorXZ(int x, int z) :
        x(x), z(z) {};
};

bool isequal(const VectorXZ& left, const VectorXZ& right) noexcept;
bool isequal(const glm::vec3& left, const glm::vec3& right) noexcept;

namespace std {
    template <> struct hash<VectorXZ> {
        size_t operator()(const VectorXZ& vect) const noexcept
        {
            std::hash<decltype(vect.x)> hasher;

            auto hash1 = hasher(vect.x);
            auto hash2 = hasher(vect.z);

            return std::hash<decltype(vect.x)>{}((hash1 ^ hash2) >> 2);
        }
    };
}

namespace std {
    template <> struct hash<glm::vec3> {
        size_t operator()(const glm::vec3& vect) const noexcept
        {
            std::hash<decltype(vect.x)> hasher;

            auto hash1 = hasher(vect.x);
            auto hash2 = hasher(vect.y);
            auto hash3 = hasher(vect.z);

            return std::hash<decltype(vect.x)>{}(
                (hash1 ^ (hash2 << hash3) ^ hash3));
        }
    };
}

#endif