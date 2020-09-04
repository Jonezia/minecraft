#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class Renderer
{
public:
    // Constructor (inits shaders/shapes)
    Renderer(Shader& shader);
    // Destructor
    ~Renderer();
    // Renders a defined quad textured with given sprite
    void DrawCube(Texture2D& texture, glm::vec3 position, glm::mat4 viewMatrix, glm::vec3 color = glm::vec3(1.0f));
private:
    // Render state
    Shader       shader;
    unsigned int cubeVAO;
    // Initializes and configures the cube's buffer and vertex attributes
    void initCubeRenderData();
};

#endif