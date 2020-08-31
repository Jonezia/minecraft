
#include <stb_image.h>

#include "game.h"
#include "camera.h"
#include "resource_manager.h"
#include "renderer.h"
#include "cube.h"

Renderer* cubeRenderer;
Camera* Player;
Cube* myCube;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), KeysProcessed(), Width(width), Height(height)
{}

Game::~Game() {
    delete Player;
}

void Game::Init() {
    Player = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // build shaders
    ResourceManager::LoadShader("source/shaders/objectVS.glsl", "source/shaders/objectFS.glsl", nullptr, "object");

    // load textures
    ResourceManager::LoadTexture("source/textures/squarebrick.jpg", false, "squareBrick");

    Shader objectShader = ResourceManager::GetShader("object");

    cubeRenderer = new Renderer(objectShader);

    myCube = new Cube(glm::vec3(0.0f, 0.0f, 0.0f), ResourceManager::GetTexture("squareBrick"));
}

void Game::ProcessKeys(float deltaTime)
{
    if (this->State == GAME_ACTIVE)
    {
        if (this->Keys[GLFW_KEY_W]) {
            Player->ProcessKeyboard(FORWARD, deltaTime);
        }
        if (this->Keys[GLFW_KEY_S]) {
            Player->ProcessKeyboard(BACKWARD, deltaTime);
        }
        if (this->Keys[GLFW_KEY_A]) {
            Player->ProcessKeyboard(LEFT, deltaTime);
        }
        if (this->Keys[GLFW_KEY_D]) {
            Player->ProcessKeyboard(RIGHT, deltaTime);
        }
        if (this->Keys[GLFW_KEY_SPACE]) {
            Player->ProcessKeyboard(UP, deltaTime);
        }
        if (this->Keys[GLFW_KEY_C]) {
            Player->ProcessKeyboard(DOWN, deltaTime);
        }
    }
}

void Game::ProcessMouseMovement(float xoffset, float yoffset)
{
    Player->ProcessMouseMovement(xoffset, yoffset);
}

void Game::Update(float dt) {

}

void Game::DoCollisions() {

}

void Game::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = Player->GetViewMatrix();
    myCube->Draw(*cubeRenderer, view);
}

void Game::ResetPlayer() {

}

void Game::ResetLevel() {

}