#include "PieceKnight.h"


PieceKnight::PieceKnight(GLchar* path, glm::vec3 position, string Color) :Piece(path, position, Color){
}


PieceKnight::~PieceKnight(){
}

void PieceKnight::FillBoard(string Chessboard[][8], string Moves[][8], int row, int col){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			Moves[i][j] = "cannot_pass";
		}
	}
	string enemy;
	if (this->Color == "white"){
		enemy = "black";
	}
	else{
		enemy = "white";
	}
	if (IsInside(row + 1, col + 2) && (Chessboard[row + 1][col + 2].find("Empty") != string::npos))	Moves[row + 1][col + 2] = "can_pass";
	if (IsInside(row + 1, col + 2) && (Chessboard[row + 1][col + 2].find(enemy) != string::npos))	Moves[row + 1][col + 2] = "can_eat";

	if (IsInside(row + 2, col + 1) && (Chessboard[row + 2][col + 1].find("Empty") != string::npos))	Moves[row + 2][col + 1] = "can_pass";
	if (IsInside(row + 2, col + 1) && (Chessboard[row + 2][col + 1].find(enemy) != string::npos))	Moves[row + 2][col + 1] = "can_eat";

	if (IsInside(row - 1, col + 2) && (Chessboard[row - 1][col + 2].find("Empty") != string::npos))	Moves[row - 1][col + 2] = "can_pass";
	if (IsInside(row -1, col + 2) && (Chessboard[row - 1][col + 2].find(enemy) != string::npos))	Moves[row - 1][col + 2] = "can_eat";

	if (IsInside(row - 2, col + 1) && (Chessboard[row - 2][col + 1].find("Empty") != string::npos))	Moves[row - 2][col + 1] = "can_pass";
	if (IsInside(row - 2, col + 1) && (Chessboard[row - 2][col + 1].find(enemy) != string::npos))	Moves[row - 2][col + 1] = "can_eat";

	if (IsInside(row + 1, col - 2) && (Chessboard[row + 1][col - 2].find("Empty") != string::npos))	Moves[row + 1][col - 2] = "can_pass";
	if (IsInside(row + 1, col - 2) && (Chessboard[row + 1][col - 2].find(enemy) != string::npos))	Moves[row + 1][col - 2] = "can_eat";

	if (IsInside(row + 2, col - 1) && (Chessboard[row + 2][col - 1].find("Empty") != string::npos))	Moves[row + 2][col - 1] = "can_pass";
	if (IsInside(row + 2, col - 1) && (Chessboard[row + 2][col - 1].find(enemy) != string::npos))	Moves[row + 2][col - 1] = "can_eat";

	if (IsInside(row - 1, col - 2) && (Chessboard[row - 1][col - 2].find("Empty") != string::npos))	Moves[row - 1][col - 2] = "can_pass";
	if (IsInside(row - 1, col - 2) && (Chessboard[row - 1][col - 2].find(enemy) != string::npos))	Moves[row - 1][col - 2] = "can_eat";

	if (IsInside(row - 2, col - 1) && (Chessboard[row - 2][col - 1].find("Empty") != string::npos))	Moves[row - 2][col - 1] = "can_pass";
	if (IsInside(row - 2, col - 1) && (Chessboard[row - 2][col - 1].find(enemy) != string::npos))	Moves[row - 2][col - 1] = "can_eat";
}

bool PieceKnight::IsInside(int row, int col){
	return ((row >= 0) && (row <= 7) && (col >= 0) && (col <= 7));
}

