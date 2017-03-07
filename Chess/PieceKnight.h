
#ifndef PIECEKINIGHT_H
#define PIECEKINIGHT_H

#include "Piece.h"
#include "string.h"
#include <glm/glm.hpp>

class PieceKnight :public Piece{
public:
	PieceKnight(GLchar* path, glm::vec3 position, string Color);
	~PieceKnight();
	void FillBoard(string Chessboard[][8], string Moves[][8], int row, int col);
private:
	bool IsInside(int row, int col);
};

#endif

