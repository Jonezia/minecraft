#include "renderer.h"
#include "resource_manager.h"

Renderer::Renderer(Shader& shader)
{
    this->shader = shader;
    this->shader.Use();
    this->shader.SetMatrix4("projection", glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f));
}

Renderer::~Renderer()
{

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