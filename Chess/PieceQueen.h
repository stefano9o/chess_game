
#ifndef PIECEQUEEN_H
#define PIECEQUEEN_H

#include "Piece.h"
#include "string.h"
#include <glm/glm.hpp>

class PieceQueen :public Piece{
public:
	PieceQueen(GLchar* path, glm::vec3 position, string Color);
	~PieceQueen();
	void FillBoard(string Chessboard[][8], string Moves[][8], int row, int col);
};

#endif
