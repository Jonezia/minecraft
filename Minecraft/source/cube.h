#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "renderer.h"

class Cube
{
public:
    // object state
    glm::vec3   Position;
    glm::vec3   Color;
    // render state
    Texture2D   Texture;
    // constructor(s)
    Cube();
    Cube(glm::vec3 pos, Texture2D texture, glm::vec3 color = glm::vec3(1.0f));
    // draw sprite
    virtual void Draw(Renderer& renderer, glm::mat4 viewMatrix);
};

#endif