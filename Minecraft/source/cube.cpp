#include "cube.h"

Cube::Cube()
    : Position(0.0f, 0.0f, 0.0f), Texture(), Color(1.0f) { }

Cube::Cube(glm::vec3 pos, Texture2D texture, glm::vec3 color)
    : Position(pos), Texture(texture), Color(color) { }

void Cube::Draw(Renderer& renderer, glm::mat4 viewMatrix)
{
    renderer.DrawCube(this->Texture, this->Position, viewMatrix, this->Color);
}