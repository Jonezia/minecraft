#include "mesh.h"
#include "world_constants.h"

Mesh::~Mesh() {
    this->vertices.clear();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::addFace(const std::array<Vertex,4> vertexData,
    const glm::vec3& chunkPosition,
    const glm::vec3& blockPosition)
{
    int posx = chunkPosition.x * CHUNK_SIZE + blockPosition.x;
    int posy = chunkPosition.y * CHUNK_SIZE + blockPosition.y;
    int posz = chunkPosition.z * CHUNK_SIZE + blockPosition.z;
    for (int i = 0; i < 4; i++) {
        vertices.push_back(
            Vertex(
                vertexData[i].position + glm::vec3(posx,posy,posz),
                vertexData[i].texCoords
            ));
    }
}

void Mesh::bufferMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // texture coord attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex,texCoords)));
}