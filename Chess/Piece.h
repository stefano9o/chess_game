
#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <glm/glm.hpp>

#include "Model.h"
#include "Shader.h"

class Piece{
public:
	Piece(GLchar* path, glm::vec3 position, string color);
	~Piece();

	void Move(glm::vec3 position);
	void Draw(Shader shader);
	virtual void FillBoard(string Chessboard[][8], string Moves[][8], int row, int col) = 0;
	bool Ate;
protected:
	glm::vec3 Position;
	Model *MyModel;
	string Color;
};

#endif

