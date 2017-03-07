#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "ResourceManager.h"

#include <iostream>


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// The Width of the screen
const GLuint FULL_SCREEN_WIDTH = 1280;
const GLuint SCREEN_WIDTH = 800;

// The height of the screen
const GLuint FULL_SCREEN_HEIGHT = 720;
const GLuint SCREEN_HEIGHT = 600;

//Game Chess(SCREEN_WIDTH, SCREEN_HEIGHT);
Game Chess(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

GLfloat lastX = 400, lastY = 300;

int main(int argc, char *argv[]){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT, "Chess", /*glfwGetPrimaryMonitor()*/ nullptr, nullptr);
	
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.


	// OpenGL configuration
	glViewport(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	// Initialize game
	Chess.Init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window) && (Chess.State != GAME_WIN)){
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Manage user input
		Chess.ProcessInput(deltaTime);

		// Update Game state
		Chess.Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Chess.Render();

		glfwSwapBuffers(window);
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Chess.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
		{
			Chess.Keys[key] = GL_FALSE;
			Chess.KeysProcessed[key] = GL_FALSE;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	//std::cout << "xpos: " << xpos << " ypos: " << ypos << std::endl;
	Chess.xpos = xpos;
	Chess.ypos = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	Chess.MyCamera.processMouseScroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	double xpos, ypos;

	if (button >= 0 && button < 8){
		if (action == GLFW_PRESS){
			Chess.MouseButton[button] = GL_TRUE;
			glfwGetCursorPos(window, &xpos, &ypos);
			Chess.xpos = xpos;
			Chess.ypos = ypos;
		}
		else if (action == GLFW_RELEASE){
			Chess.MouseButton[button] = GL_FALSE;
			Chess.MouseButtonProcessed[button] = GL_FALSE;
		}
	}

}
