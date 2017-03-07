#include "PiecePawn.h"

PiecePawn::PiecePawn(GLchar* path, glm::vec3 position, string Color) :Piece(path, position, Color){
	FirstMove = true;
}

void PiecePawn::FillBoard(string Chessboard[][8], string Moves[][8], int row, int col){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			Moves[i][j] = "cannot_pass";
		}

	}
	if ((row == 0) || (row == 7)){
		return;
	}

	int direction;
	string enemy;
	if (this->Color == "white"){
		direction = +1;
		enemy = "black";
	}
		
	else{
		direction = -1;
		enemy = "white";
	}
	if (Chessboard[row + direction][col].find("Empty") != string::npos){
		Moves[row + direction][col] = "can_pass";
	}

	if ((Chessboard[row + direction][col - 1].find(enemy) != string::npos) &&
		(col > 0)){
		Moves[row + direction][col - 1] = "can_eat";
	}
	if ((Chessboard[row + direction][col + 1].find(enemy) != string::npos) &&
		(col < 7)){
		Moves[row + direction][col + 1] = "can_eat";
	}
	
	//if (FirstMove){
	if ((row == 1) && (Chessboard[row][col].find("white") != string::npos) || (row == 6) && (Chessboard[row][col].find("black") != string::npos)){
		direction *= 2;
		if (Chessboard[row + direction][col].find("Empty") != string::npos){
			Moves[row + direction][col] = "can_pass";
		}
		FirstMove = false;
	}
}
