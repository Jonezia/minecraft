#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoords;
	Vertex(glm::vec3 aposition, glm::vec2 atexCoords) :
		position(aposition), texCoords(atexCoords) {}
};

#endif