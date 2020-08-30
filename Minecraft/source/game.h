#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum GameState {
	GAME_MENU,
	GAME_ACTIVE
};

class Game
{
public:
	// Game info
	GameState State;
	bool Keys[1024];
	bool KeysProcessed[1024];
	unsigned int Width, Height;

	// Constructor/Destructor
	Game(unsigned int width, unsigned int height);
	~Game();
	// Initialise Game
	void Init();
	// Game loop
	void ProcessKeys(float dt);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void Update(float dt);
	void DoCollisions();
	void Render();
	// Reset
	void ResetPlayer();
	void ResetLevel();
};

#endif