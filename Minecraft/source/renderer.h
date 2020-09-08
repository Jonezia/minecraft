#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "world/mesh.h"

class Renderer
{
public:
    // Constructor (inits shaders/shapes)
    Renderer(Shader& shader);
    // Destructor
    ~Renderer();
    // Renders a defined quad textured with given sprite
    void DrawCube(glm::vec3 position, glm::mat4 viewMatrix);
    void drawChunk(const Mesh& mesh, glm::mat4 viewMatrix);
    // Initializes and configures the cube's buffer and vertex attributes
    void initCubeRenderData();
private:
    // Render state
    Shader       shader;
    unsigned int cubeVAO;
};

#endif