
#include <stb_image.h>

#include "game.h"
#include "camera.h"
#include "resource_manager.h"
#include "renderer.h"
#include "world/world.h"
#include "text_renderer.h"

Renderer* masterRenderer;
Camera* Player;
World* world;
TextRenderer* Text;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), KeysProcessed(), Width(width), Height(height)
{}

Game::~Game() {
    delete masterRenderer;
    delete Player;
    delete world;
    delete Text;
}

void Game::Init() {
    Player = new Camera(glm::vec3(5.0f, 2.0f, 5.0f));

    // build shaders
    ResourceManager::LoadShader("source/shaders/objectVS.glsl", "source/shaders/objectFS.glsl", nullptr, "object");

    // load textures
    ResourceManager::LoadTexture("source/textures/default-texture-pack.png", false, "textureAtlas");

    Shader objectShader = ResourceManager::GetShader("object");
    masterRenderer = new Renderer(objectShader);

    Text = new TextRenderer(Width, Height);
    Text->Load("source/fonts/calibri.ttf", 24);

    world = new World();
    world->setSpawn(*Player);
}

void Game::ProcessKeys(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        if (this->Keys[GLFW_KEY_W]) {
            Player->ProcessKeyboard(FORWARD, dt);
        }
        if (this->Keys[GLFW_KEY_S]) {
            Player->ProcessKeyboard(BACKWARD, dt);
        }
        if (this->Keys[GLFW_KEY_A]) {
            Player->ProcessKeyboard(LEFT, dt);
        }
        if (this->Keys[GLFW_KEY_D]) {
            Player->ProcessKeyboard(RIGHT, dt);
        }
        if (this->Keys[GLFW_KEY_SPACE]) {
            Player->ProcessKeyboard(UP, dt);
        }
        if (this->Keys[GLFW_KEY_C]) {
            Player->ProcessKeyboard(DOWN, dt);
        }
    }
}

void Game::ProcessMouseMovement(float xoffset, float yoffset)
{
    Player->ProcessMouseMovement(xoffset, yoffset);
}

void Game::Update(float dt) {
    world->loadSurroundingChunks(*Player);
}

void Game::DoCollisions() {

}

void Game::Render(float dt) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world->render(*masterRenderer, *Player);

    int fps = 1 / dt;
    Text->RenderText(std::to_string(fps) + " fps", 5.0f, 5.0f, 1.0f);

    std::pair<int, int> XZPos = world->getCurrentChunk();
    std::string currChunk = "Current Chunk ( " + std::to_string(XZPos.first) 
        + ", " + std::to_string(XZPos.second) + ")";
    Text->RenderText(currChunk, 5.0f, 30.0f, 1.0f);
}

void Game::ResetPlayer() {

}

void Game::ResetLevel() {

}