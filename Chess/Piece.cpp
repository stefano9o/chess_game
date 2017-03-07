
#include "Piece.h"

#include "ResourceManager.h"

Piece::Piece(GLchar* path,glm::vec3 position, string color){
	this->Position = position;
	MyModel = new Model(path);
	this->Color = color; 
	Ate = false;
}

Piece::~Piece(){
}

void Piece::Move(glm::vec3 position){
	this->Position = position;
}

void Piece::Draw(Shader shader){
	glm::mat4 model;
	model = glm::translate(model, Position);
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.SetMatrix4("model", model);
	MyModel->Draw(shader);
}
