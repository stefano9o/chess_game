
#ifndef PIECEPAWN_H
#define PIECEPAWN_H

#include "Piece.h"
#include "string.h"
#include <glm/glm.hpp>

class PiecePawn : public Piece{
public:
	PiecePawn(GLchar* path, glm::vec3 position, string Color);
	void FillBoard(string Chessboard[][8], string Moves[][8], int row, int col);
private:
	bool FirstMove;
};

#endif