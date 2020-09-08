#include "renderer.h"
#include "resource_manager.h"

Renderer::Renderer(Shader& shader)
{
    this->shader = shader;
    this->shader.Use();
    this->shader.SetMatrix4("projection", glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f));
    this->initCubeRenderData();
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &this->cubeVAO);
}

void Renderer::DrawCube(glm::vec3 position, glm::mat4 viewMatrix)
{
    // prepare transformations
    this->shader.Use();

    // camera/view transformation
    glm::mat4 view = viewMatrix;

    // create transformations
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3(position));

    this->shader.SetMatrix4("model", model);
    this->shader.SetMatrix4("view",viewMatrix);

    // render textured cube
    this->shader.SetVector3f("color", glm::vec3(1.0, 1.0, 1.0));

    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture("squareBrick").Bind();

    glBindVertexArray(this->cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Renderer::initCubeRenderData()
{
    float vertices[] = {
        // position           // texCoord
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int VBO;
    glGenVertexArrays(1, &this->cubeVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Renderer::drawChunk(const Mesh& mesh, glm::mat4 viewMatrix)
{
    // prepare transformations
    this->shader.Use();

    // camera/view transformation
    glm::mat4 view = viewMatrix;

    // create transformations
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

    this->shader.SetMatrix4("model", model);
    this->shader.SetMatrix4("view", viewMatrix);

    this->shader.SetVector3f("color", glm::vec3(1.0,1.0,1.0));

    glActiveTexture(GL_TEXTURE0);
    // Replace with proper texture
    ResourceManager::GetTexture("squareBrick").Bind();

    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.vertices.size(), GL_UNSIGNED_INT, 0);
}