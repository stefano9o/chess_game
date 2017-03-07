
#ifndef PIECEBISHOP_H
#define PIECEBISHOP_H

#include "Piece.h"
#include "string.h"
#include <glm/glm.hpp>

class PieceBishop :public Piece{
public:
	PieceBishop(GLchar* path, glm::vec3 position, string Color);
	~PieceBishop();
	void FillBoard(string Chessboard[][8], string Moves[][8], int row, int col);
};

#endif