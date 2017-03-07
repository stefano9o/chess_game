
#include "Quad.h"
#include "ResourceManager.h"

#include <iostream>
using namespace std;


Quad::Quad(int Width, int Height, Camera *MyCamera){
	this->Width = Width;
	this->Height = Height;
	this->MyCamera = MyCamera;

	ResourceManager::LoadShader("shaders/selection.vs", "shaders/selection.frag", nullptr, "selection");

	GLfloat vertices[] = {
		// Positions         // Normals        // Texture Coords	// Color
		0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// Top Right
		0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// Bottom Right
		-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// Bottom Left
		-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// Bottom Left
		-0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// Top Left 
		0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f	// Top Right
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 12 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, 0, 12 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, 0, 12 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 4, GL_FLOAT, 0, 12 * sizeof(GLfloat), (void *)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_VERTEX_ARRAY, 0);
}

void Quad::Render(glm::vec3 position){
	ResourceManager::GetShader("selection").Use();

	glm::mat4 view;
	glm::mat4 projection;

	view = MyCamera->getViewMatrix();
	projection = glm::perspective(MyCamera->getZoom(), (float)Width / (float)Height, 0.1f, 1000.0f);

	glm::mat4 model = glm::mat4();
	model = glm::translate(model, position);

	ResourceManager::GetShader("selection").SetMatrix4("view", view);
	ResourceManager::GetShader("selection").SetMatrix4("projection", projection);
	ResourceManager::GetShader("selection").SetMatrix4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);
}


Quad::~Quad(){
}
