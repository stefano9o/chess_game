#include "PieceKing.h"


PieceKing::PieceKing(GLchar* path, glm::vec3 position, string Color) :Piece(path, position, Color){
}


PieceKing::~PieceKing(){
}

void PieceKing::FillBoard(string Chessboard[][8], string Moves[][8], int row, int col){
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

	if (IsInside(row + 1, col + 0) && (Chessboard[row + 1][col + 0].find("Empty") != string::npos))	Moves[row + 1][col + 0] = "can_move";
	if (IsInside(row + 1, col + 0) && (Chessboard[row + 1][col + 0].find(enemy) != string::npos))	Moves[row + 1][col + 0] = "can_eat";

	if (IsInside(row + 1, col + 1) && (Chessboard[row + 1][col + 1].find("Empty") != string::npos))	Moves[row + 1][col + 1] = "can_move";
	if (IsInside(row + 1, col + 1) && (Chessboard[row + 1][col + 1].find(enemy) != string::npos))	Moves[row + 1][col + 1] = "can_eat";

	if (IsInside(row + 0, col + 1) && (Chessboard[row + 0][col + 1].find("Empty") != string::npos))	Moves[row + 0][col + 1] = "can_move";
	if (IsInside(row + 0, col + 1) && (Chessboard[row + 0][col + 1].find(enemy) != string::npos))	Moves[row + 0][col + 1] = "can_eat";

	if (IsInside(row - 1, col + 1) && (Chessboard[row - 1][col + 1].find("Empty") != string::npos))	Moves[row - 1][col + 1] = "can_move";
	if (IsInside(row - 1, col + 1) && (Chessboard[row - 1][col + 1].find(enemy) != string::npos))	Moves[row - 1][col + 1] = "can_eat";

	if (IsInside(row - 1, col + 0) && (Chessboard[row - 1][col + 0].find("Empty") != string::npos))	Moves[row - 1][col + 0] = "can_move";
	if (IsInside(row - 1, col + 0) && (Chessboard[row - 1][col + 0].find(enemy) != string::npos))	Moves[row - 1][col + 0] = "can_eat";

	if (IsInside(row - 1, col - 1) && (Chessboard[row - 1][col - 1].find("Empty") != string::npos))	Moves[row - 1][col - 1] = "can_move";
	if (IsInside(row - 1, col - 1) && (Chessboard[row - 1][col - 1].find(enemy) != string::npos))	Moves[row - 1][col - 1] = "can_eat";

	if (IsInside(row + 0, col - 1) && (Chessboard[row + 0][col - 1].find("Empty") != string::npos))	Moves[row + 0][col - 1] = "can_move";
	if (IsInside(row + 0, col - 1) && (Chessboard[row + 0][col - 1].find(enemy) != string::npos))	Moves[row + 0][col - 1] = "can_eat";

	if (IsInside(row + 1, col - 1) && (Chessboard[row + 1][col - 1].find("Empty") != string::npos))	Moves[row + 1][col - 1] = "can_move";
	if (IsInside(row + 1, col - 1) && (Chessboard[row + 1][col - 1].find(enemy) != string::npos))	Moves[row + 1][col - 1] = "can_eat";

}

bool PieceKing::IsInside(int row, int col){
	return ((row >= 0) && (row <= 7) && (col >= 0) && (col <= 7));
}