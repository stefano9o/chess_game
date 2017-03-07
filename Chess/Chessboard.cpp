#include "Chessboard.h"


Chessboard::Chessboard(GLchar* path){
	MyModel = new Model(path);
}


Chessboard::~Chessboard(){
}

void Chessboard::Draw(Shader shader){
	glm::mat4 model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, -0.15f, 0.0f));
	shader.SetMatrix4("model", model);
	MyModel->Draw(shader);
}
