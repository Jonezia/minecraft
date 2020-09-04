#include "vector_hash.h"

bool isequal(const VectorXZ& left, const VectorXZ& right) noexcept
{
	return (left.x == right.x) && (left.z == right.z);
}

bool isequal(const glm::vec3& left, const glm::vec3& right) noexcept
{
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}