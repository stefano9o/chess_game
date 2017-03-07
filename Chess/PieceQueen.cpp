#include "PieceQueen.h"


PieceQueen::PieceQueen(GLchar* path, glm::vec3 position, string Color) :Piece(path, position, Color){
}


PieceQueen::~PieceQueen(){
}

void PieceQueen::FillBoard(string Chessboard[][8], string Moves[][8], int row, int col){
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

	int IncRow = row;
	int IncCol = col;
	
	//move down
	while (IncRow > 0){
		IncRow--;

		if (Chessboard[IncRow][IncCol].find("Empty") != string::npos){
			Moves[IncRow][IncCol] = "can_pass";
		}
		else if (Chessboard[IncRow][IncCol].find(enemy) != string::npos){
			Moves[IncRow][IncCol] = "can_eat";
			break;
		}
		else{
			break;
		}
	}
	IncRow = row;
	IncCol = col;
	//move up
	while (IncRow < 7){
		IncRow++;

		if (Chessboard[IncRow][IncCol].find("Empty") != string::npos){
			Moves[IncRow][IncCol] = "can_pass";
		}
		else if (Chessboard[IncRow][IncCol].find(enemy) != string::npos){
			Moves[IncRow][IncCol] = "can_eat";
			break;
		}
		else{
			break;
		}
	}
	IncRow = row;
	IncCol = col;
	//move left
	while (IncCol > 0){
		IncCol--;

		if (Chessboard[IncRow][IncCol].find("Empty") != string::npos){
			Moves[IncRow][IncCol] = "can_pass";
		}
		else if (Chessboard[IncRow][IncCol].find(enemy) != string::npos){
			Moves[IncRow][IncCol] = "can_eat";
			break;
		}
		else{
			break;
		}
	}
	IncRow = row;
	IncCol = col;
	//move right
	while (IncCol < 7){
		IncCol++;

		if (Chessboard[IncRow][IncCol].find("Empty") != string::npos){
			Moves[IncRow][IncCol] = "can_pass";
		}
		else if (Chessboard[IncRow][IncCol].find(enemy) != string::npos){
			Moves[IncRow][IncCol] = "can_eat";
			break;
		}
		else{
			break;
		}
	}
	IncRow = row;
	IncCol = col;
	//move left-down
	while ((IncRow > 0) && (IncCol > 0)){
		IncRow--;
		IncCol--;

		if (Chessboard[IncRow][IncCol].find("Empty") != string::npos){
			Moves[IncRow][IncCol] = "can_pass";
		}
		else if (Chessboard[IncRow][IncCol].find(enemy) != string::npos){
			Moves[IncRow][IncCol] = "can_eat";
			break;
		}
		else{
			break;
		}
	}
	IncRow = row;
	IncCol = col;
	//move right-down
	while ((IncRow > 0) && (IncCol < 7)){
		IncRow--;
		IncCol++;

		if (Chessboard[IncRow][IncCol].find("Empty") != string::npos){
			Moves[IncRow][IncCol] = "can_pass";
		}
		else if (Chessboard[IncRow][IncCol].find(enemy) != string::npos){
			Moves[IncRow][IncCol] = "can_eat";
			break;
		}
		else{
			break;
		}
	}
	IncRow = row;
	IncCol = col;
	//move left-up
	while ((IncRow < 7) && (IncCol > 0)){
		IncRow++;
		IncCol--;

		if (Chessboard[IncRow][IncCol].find("Empty") != string::npos){
			Moves[IncRow][IncCol] = "can_pass";
		}
		else if (Chessboard[IncRow][IncCol].find(enemy) != string::npos){
			Moves[IncRow][IncCol] = "can_eat";
			break;
		}
		else{
			break;
		}
	}
	IncRow = row;
	IncCol = col;
	//move right-up
	while ((IncRow < 7) && (IncCol < 7)){
		IncRow++;
		IncCol++;

		if (Chessboard[IncRow][IncCol].find("Empty") != string::npos){
			Moves[IncRow][IncCol] = "can_pass";
		}
		else if (Chessboard[IncRow][IncCol].find(enemy) != string::npos){
			Moves[IncRow][IncCol] = "can_eat";
			break;
		}
		else{
			break;
		}
	}
}
