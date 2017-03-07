
#ifndef QUAD_H
#define QUAD_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Camera.h"

class Quad{
public:
	Quad(int Width, int Height, Camera *MyCamera);
	~Quad();

	void Render(glm::vec3 position);
private:
	// Render state
	GLuint VAO, VBO;
	int Width, Height;
	Camera *MyCamera;
};

#endif