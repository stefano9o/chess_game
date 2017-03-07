
#ifndef PIECEKNIGHT_H
#define PIECEKNIGHT_H

#include "Piece.h"
#include "string.h"
#include <glm/glm.hpp>

class PieceKing :public Piece{
public:
	PieceKing(GLchar* path, glm::vec3 position, string Color);
	~PieceKing();
	void FillBoard(string Chessboard[][8], string Moves[][8], int row, int col);

	bool IsInside(int row,int col);
};

#endif
