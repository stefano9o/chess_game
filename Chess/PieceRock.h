
#ifndef PIECEROCK_H
#define PIECEROCK_H

#include "Piece.h"
#include "string.h"
#include <glm/glm.hpp>

class PieceRock :public Piece{
public:
	PieceRock(GLchar* path, glm::vec3 position, string Color);
	~PieceRock();
	void FillBoard(string Chessboard[][8], string Moves[][8], int row, int col);
};

#endif