
#ifndef GAME_H
#define GAME_H
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Camera.h"

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_WIN
};

class Game
{
public:
	// Game state
	GameState              State;
	GLboolean              Keys[1024];
	GLboolean              KeysProcessed[1024];
	GLboolean			   MouseButton[8];
	GLboolean			   MouseButtonProcessed[8];
	double				   xpos, ypos;
	GLuint                 Width, Height;
	Camera				   MyCamera;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/models)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
private:
	glm::vec3 CalculateIntersection();
	glm::vec3 CalculateCoordinates(int row, int col);
	glm::vec3 CalculateRay(int xpos, int ypos, glm::mat4 projection, glm::mat4 view);
	GLuint loadCubemap(vector<const GLchar*> faces);
};

#endif