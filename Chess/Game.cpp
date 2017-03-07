#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Model.h"
#include "ChessGame.h"
#include "TextRenderer.h"
#include "Quad.h"
// Other Libs
#include <SOIL.h>

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include <irrklang/irrKlang.h>
using namespace irrklang;

#define LENGTH_CHESSBOARD (1.797 * 5)
#define LENGTH_CELL (LENGTH_CHESSBOARD / 8)

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f, -3.0f, 0.0f),
	glm::vec3(-1.7f, 0.9f, 1.0f)
};

bool firstMouse = true;

float lastPosX = 0;
float lastPosY = 0;

ChessGame *chessGame;
ISoundEngine *SoundEngine = createIrrKlangDevice();

GLfloat skyboxVertices[] = {
	// Positions          
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

GLuint skyboxVAO, skyboxVBO;
GLuint cubemapTexture;

Game::Game(GLuint width, GLuint height){
	this->Width = width;
	this->Height = height;
	MyCamera = Camera(glm::vec3(-10.0f, 9.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f);
}

Game::~Game(){

}

void Game::Init(){
	// Load shaders
	ResourceManager::LoadShader("shaders/lighting.vs", "shaders/lighting.frag", nullptr, "lighting");
	// Use Shader
	ResourceManager::GetShader("lighting").Use();
	// Point light 1
	ResourceManager::GetShader("lighting").SetVector3f("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
	ResourceManager::GetShader("lighting").SetVector3f("pointLights[0].ambient", 1.0f, 1.0f, 1.0f);
	ResourceManager::GetShader("lighting").SetVector3f("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
	ResourceManager::GetShader("lighting").SetVector3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	ResourceManager::GetShader("lighting").SetFloat("pointLights[0].constant", 1.0f);
	ResourceManager::GetShader("lighting").SetFloat("pointLights[0].linear", 0.09f);
	ResourceManager::GetShader("lighting").SetFloat("pointLights[0].quadratic", 0.032f);
	// Set material properties
	ResourceManager::GetShader("lighting").SetFloat("material.shininess", 32.0f);
	State = GAME_ACTIVE;
	chessGame = new ChessGame(Width, Height, &MyCamera, SoundEngine);
	
	chessGame->Init();

	ResourceManager::LoadShader("shaders/skybox.vs", "shaders/skybox.frag", nullptr, "skybox");
	// Setup skybox VAO
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	// Cubemap (Skybox)
	vector<const GLchar*> faces;
	faces.push_back("skybox/right.jpg");
	faces.push_back("skybox/left.jpg");
	faces.push_back("skybox/top.jpg");
	faces.push_back("skybox/bottom.jpg");
	faces.push_back("skybox/back.jpg");
	faces.push_back("skybox/front.jpg");
	cubemapTexture = loadCubemap(faces);

	// Load audio
	SoundEngine->play2D("audio/background.mp3", GL_TRUE);
}

void Game::Update(GLfloat dt){
	if (State == GAME_ACTIVE){
		if (MouseButton[GLFW_MOUSE_BUTTON_LEFT] && !MouseButtonProcessed[GLFW_MOUSE_BUTTON_LEFT]) {
			chessGame->clicked = true;
			MouseButtonProcessed[GLFW_MOUSE_BUTTON_LEFT] = GLU_TRUE;
			if (chessGame->IsTurnBlack() && chessGame->IsThereAWinner()){
				State = GAME_WIN;
			}
			if (chessGame->IsTurnWhite() && chessGame->IsThereAWinner()){
				State = GAME_WIN;
			}
		}
		chessGame->xpos = xpos;
		chessGame->ypos = ypos;
	}
	if (State == GAME_WIN){
		cout << "Hai vinto" << endl;
	}
 }


void Game::ProcessInput(GLfloat dt){
	
	// Camera controls
	if (Keys[GLFW_KEY_W] && !KeysProcessed[GLFW_KEY_W])
		MyCamera.processKeyboard(FORWARD, dt);

	if (Keys[GLFW_KEY_S] && !KeysProcessed[GLFW_KEY_S])
		MyCamera.processKeyboard(BACKWARD, dt);

	if (Keys[GLFW_KEY_A] && !KeysProcessed[GLFW_KEY_A])
		MyCamera.processKeyboard(LEFT, dt);

	if (Keys[GLFW_KEY_D] && !KeysProcessed[GLFW_KEY_D])
		MyCamera.processKeyboard(RIGHT, dt);
	
	if (MouseButton[GLFW_MOUSE_BUTTON_MIDDLE] && !MouseButtonProcessed[GLFW_MOUSE_BUTTON_MIDDLE]){
		if (firstMouse)
		{
			lastPosX = xpos;
			lastPosY = ypos;
			firstMouse = false;
		}

		GLfloat xoffset = xpos - lastPosX;
		GLfloat yoffset = lastPosY - ypos;  // Reversed since y-coordinates go from bottom to left

		lastPosX = xpos;
		lastPosY = ypos;

		MyCamera.processMouseMovement(xoffset, yoffset);
	}
}

void Game::Render(){
	// Draw skybox first
	glDepthMask(GL_FALSE);// Remember to turn depth writing off
	ResourceManager::GetShader("skybox").Use();
	glm::mat4 view = glm::mat4(glm::mat3(MyCamera.getViewMatrix()));	// Remove any translation component of the view matrix
	glm::mat4 projection = glm::perspective(MyCamera.getZoom(), (float)Width / (float)Height, 0.1f, 100.0f);
	ResourceManager::GetShader("skybox").SetMatrix4("view", view);
	ResourceManager::GetShader("skybox").SetMatrix4("projection", projection);
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);

	ResourceManager::GetShader("skybox").SetInteger("skybox",0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);

	chessGame->Draw(ResourceManager::GetShader("lighting"));
}

GLuint Game::loadCubemap(vector<const GLchar*> faces){
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}