#include "ChessGame.h"

#include <iostream>
#include "ResourceManager.h"

int LastRowWhite = 0;
int LastColWhite = 9;

int LastRowBlack = 7;
int LastColBlack = -2;

int LastRowPawn, LastColPawn;

ChessGame::ChessGame(int Width, int Height, Camera *MyCamera, ISoundEngine *SoundEngine){
	this->Width = Width;
	this->Height = Height;
	this->MyCamera = MyCamera;
	this->SoundEngine = SoundEngine;
}


ChessGame::~ChessGame(){
}

void ChessGame::Init(){
	CurrentTurn = TURN_WHITE;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			ChessboardState[i][j] = "Empty";
		}
	}

	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 4; ++j){
			CemeteryState[i][j] = "Empty";
		}
	}

	MyChessboard = new Chessboard("objects/chessboard.obj");

	Pieces["Rock1_white"] = new PieceRock("objects/rock_white.obj", CalculateCoordinates(0, 0), "white");
	ChessboardState[0][0] = "Rock1_white";
	Pieces["Knight1_white"] = new PieceKnight("objects/knight_white.obj", CalculateCoordinates(0, 1), "white");
	ChessboardState[0][1] = "Knight1_white";
	Pieces["Bishop1_white"] = new PieceBishop("objects/bishop_white.obj", CalculateCoordinates(0, 2), "white");
	ChessboardState[0][2] = "Bishop1_white";
	Pieces["Queen_white"] = new PieceQueen("objects/queen_white.obj", CalculateCoordinates(0, 3), "white");
	ChessboardState[0][3] = "Queen_white";
	Pieces["King_white"] = new PieceKing("objects/king_white.obj", CalculateCoordinates(0, 4), "white");
	ChessboardState[0][4] = "King_white";
	Pieces["Bishop2_white"] = new PieceBishop("objects/bishop_white.obj", CalculateCoordinates(0, 5), "white");
	ChessboardState[0][5] = "Bishop2_white";
	Pieces["Knight2_white"] = new PieceKnight("objects/knight_white.obj", CalculateCoordinates(0, 6), "white");
	ChessboardState[0][6] = "Knight2_white";
	Pieces["Rock2_white"] = new  PieceRock("objects/rock_white.obj", CalculateCoordinates(0, 7), "white");
	ChessboardState[0][7] = "Rock2_white";
	Pieces["Pawn1_white"] = new PiecePawn("objects/pawn_white.obj", CalculateCoordinates(1, 0), "white");
	ChessboardState[1][0] = "Pawn1_white";
	Pieces["Pawn2_white"] = new PiecePawn("objects/pawn_white.obj", CalculateCoordinates(1, 1), "white");
	ChessboardState[1][1] = "Pawn2_white";
	Pieces["Pawn3_white"] = new PiecePawn("objects/pawn_white.obj", CalculateCoordinates(1, 2), "white");
	ChessboardState[1][2] = "Pawn3_white";
	Pieces["Pawn4_white"] = new PiecePawn("objects/pawn_white.obj", CalculateCoordinates(1, 3), "white");
	ChessboardState[1][3] = "Pawn4_white";
	Pieces["Pawn5_white"] = new PiecePawn("objects/pawn_white.obj", CalculateCoordinates(1, 4), "white");
	ChessboardState[1][4] = "Pawn5_white";
	Pieces["Pawn6_white"] = new PiecePawn("objects/pawn_white.obj", CalculateCoordinates(1, 5), "white");
	ChessboardState[1][5] = "Pawn6_white";
	Pieces["Pawn7_white"] = new PiecePawn("objects/pawn_white.obj", CalculateCoordinates(1, 6), "white");
	ChessboardState[1][6] = "Pawn7_white";
	Pieces["Pawn8_white"] = new PiecePawn("objects/pawn_white.obj", CalculateCoordinates(1, 7), "white");
	ChessboardState[1][7] = "Pawn8_white";

	Pieces["Rock1_black"] = new PieceRock("objects/rock_black.obj", CalculateCoordinates(7, 0), "black");
	ChessboardState[7][0] = "Rock1_black";
	Pieces["Knight1_black"] = new PieceKnight("objects/knight_black.obj", CalculateCoordinates(7, 1), "knight");
	ChessboardState[7][1] = "Knight1_black";
	Pieces["Bishop1_black"] = new PieceBishop("objects/bishop_black.obj", CalculateCoordinates(7, 2), "black");
	ChessboardState[7][2] = "Bishop1_black";
	Pieces["Queen_black"] = new PieceQueen("objects/queen_black.obj", CalculateCoordinates(7, 3), "black");
	ChessboardState[7][3] = "Queen_black";
	Pieces["King_black"] = new PieceKing("objects/king_black.obj", CalculateCoordinates(7, 4), "black");
	ChessboardState[7][4] = "King_black";
	Pieces["Bishop2_black"] = new PieceBishop("objects/bishop_black.obj", CalculateCoordinates(7, 5), "black");
	ChessboardState[7][5] = "Bishop2_black";
	Pieces["Knight2_black"] = new PieceKnight("objects/knight_black.obj", CalculateCoordinates(7, 6), "knight");
	ChessboardState[7][6] = "Knight2_black";
	Pieces["Rock2_black"] = new PieceRock("objects/rock_black.obj", CalculateCoordinates(7, 7), "black");
	ChessboardState[7][7] = "Rock2_black";
	Pieces["Pawn1_black"] = new PiecePawn("objects/pawn_black.obj", CalculateCoordinates(6, 0), "black");
	ChessboardState[6][0] = "Pawn1_black";
	Pieces["Pawn2_black"] = new PiecePawn("objects/pawn_black.obj", CalculateCoordinates(6, 1), "black");
	ChessboardState[6][1] = "Pawn2_black";
	Pieces["Pawn3_black"] = new PiecePawn("objects/pawn_black.obj", CalculateCoordinates(6, 2), "black");
	ChessboardState[6][2] = "Pawn3_black";
	Pieces["Pawn4_black"] = new PiecePawn("objects/pawn_black.obj", CalculateCoordinates(6, 3), "black");
	ChessboardState[6][3] = "Pawn4_black";
	Pieces["Pawn5_black"] = new PiecePawn("objects/pawn_black.obj", CalculateCoordinates(6, 4), "black");
	ChessboardState[6][4] = "Pawn5_black";
	Pieces["Pawn6_black"] = new PiecePawn("objects/pawn_black.obj", CalculateCoordinates(6, 5), "black");
	ChessboardState[6][5] = "Pawn6_black";
	Pieces["Pawn7_black"] = new PiecePawn("objects/pawn_black.obj", CalculateCoordinates(6, 6), "black");
	ChessboardState[6][6] = "Pawn7_black";
	Pieces["Pawn8_black"] = new PiecePawn("objects/pawn_black.obj", CalculateCoordinates(6, 7), "black");
	ChessboardState[6][7] = "Pawn8_black";

	Selection = new Quad(Width, Height, MyCamera);
}
void ChessGame::Draw(Shader shader){
	ResourceManager::GetShader("lighting").Use();

	glm::mat4 view;
	glm::mat4 projection;

	view = MyCamera->getViewMatrix();
	projection = glm::perspective(MyCamera->getZoom(), (float)Width / (float)Height, 0.1f, 1000.0f);

	glm::mat4 model = glm::mat4();

	ResourceManager::GetShader("lighting").SetMatrix4("view", view);
	ResourceManager::GetShader("lighting").SetMatrix4("projection", projection);
	ResourceManager::GetShader("lighting").SetMatrix4("model", model);
	MyChessboard->Draw(shader);

	Pieces["Rock1_white"]->Draw(shader);
	Pieces["Knight1_white"]->Draw(shader);
	Pieces["Bishop1_white"]->Draw(shader);
	Pieces["Queen_white"]->Draw(shader);
	Pieces["King_white"]->Draw(shader);
	Pieces["Bishop2_white"]->Draw(shader);
	Pieces["Knight2_white"]->Draw(shader);
	Pieces["Rock2_white"]->Draw(shader);
	Pieces["Pawn1_white"]->Draw(shader);
	Pieces["Pawn2_white"]->Draw(shader);
	Pieces["Pawn3_white"]->Draw(shader);
	Pieces["Pawn4_white"]->Draw(shader);
	Pieces["Pawn5_white"]->Draw(shader);
	Pieces["Pawn6_white"]->Draw(shader);
	Pieces["Pawn7_white"]->Draw(shader);
	Pieces["Pawn8_white"]->Draw(shader);

	Pieces["Rock1_black"]->Draw(shader);
	Pieces["Knight1_black"]->Draw(shader);
	Pieces["Bishop1_black"]->Draw(shader);
	Pieces["Queen_black"]->Draw(shader);
	Pieces["King_black"]->Draw(shader);
	Pieces["Bishop2_black"]->Draw(shader);
	Pieces["Knight2_black"]->Draw(shader);
	Pieces["Rock2_black"]->Draw(shader);
	Pieces["Pawn1_black"]->Draw(shader);
	Pieces["Pawn2_black"]->Draw(shader);
	Pieces["Pawn3_black"]->Draw(shader);
	Pieces["Pawn4_black"]->Draw(shader);
	Pieces["Pawn5_black"]->Draw(shader);
	Pieces["Pawn6_black"]->Draw(shader);
	Pieces["Pawn7_black"]->Draw(shader);
	Pieces["Pawn8_black"]->Draw(shader);

	//define normal of plane with we need to calculate intersaction
	glm::vec3 n(0.0f, 1.0f, 0.0f);
	glm::vec3 o = MyCamera->getPosition();
	glm::vec3 d = CalculateRay();

	//plane has 0 ypos
	float t = -((glm::dot(o, n)) / glm::dot(d, n));
	glm::vec3 p(o + d*t);
	bool win = false;
	//CurrentTurnState = RESCUE;
	switch (CurrentTurnState){
		case SELECTION:
			if ((p.x > (-LENGTH_CHESSBOARD / 2)) && (p.x < (LENGTH_CHESSBOARD / 2)) &&
				(p.z >(-LENGTH_CHESSBOARD / 2)) && (p.z < (LENGTH_CHESSBOARD / 2))){
				CalculateCell(p);
			}

			Selection->Render(CalculateCoordinates(CurrentRow, CurrentCol));
			if (clicked == true){
				if (IsWhite(ChessboardState[CurrentRow][CurrentCol]) && CurrentTurn == TURN_WHITE){
					PieceSelected = ChessboardState[CurrentRow][CurrentCol];
					InitRowPieceSelected = CurrentRow;
					InitColPieceSelected = CurrentCol;
					Pieces[PieceSelected]->FillBoard(ChessboardState, Moves, CurrentRow, CurrentCol);
					CalculateMoves(Moves);
					CurrentTurnState = MOVEMENT;
				}
				else if (IsBlack(ChessboardState[CurrentRow][CurrentCol]) && CurrentTurn == TURN_BLACK){
					PieceSelected = ChessboardState[CurrentRow][CurrentCol];
					InitRowPieceSelected = CurrentRow;
					InitColPieceSelected = CurrentCol;
					Pieces[PieceSelected]->FillBoard(ChessboardState, Moves, CurrentRow, CurrentCol);
					CalculateMoves(Moves);
					CurrentTurnState = MOVEMENT;
				}
				clicked = false;
			}

			break;
		case MOVEMENT:
			if ((p.x > (-LENGTH_CHESSBOARD / 2)) && (p.x < (LENGTH_CHESSBOARD / 2)) &&
				(p.z >(-LENGTH_CHESSBOARD / 2)) && (p.z < (LENGTH_CHESSBOARD / 2))){
				CalculateCell(p);
			}

			Pieces[PieceSelected]->Move(CalculateCoordinates(CurrentRow, CurrentCol));
		
			if (clicked == true){
				Moves[InitRowPieceSelected][InitColPieceSelected] = "can_pass";
				if (Moves[CurrentRow][CurrentCol].find("cannot_pass") == string::npos){
					ChessboardState[InitRowPieceSelected][InitColPieceSelected] = "Empty";
					if (Moves[CurrentRow][CurrentCol].find("can_eat") != string::npos){
						if (ChessboardState[CurrentRow][CurrentCol].find("white") != string::npos){
							Pieces[ChessboardState[CurrentRow][CurrentCol]]->Move(CalculateCoordinates(LastRowWhite, LastColWhite));
							
							CemeteryState[LastRowWhite][LastColWhite - 7] = ChessboardState[CurrentRow][CurrentCol];
							LastRowWhite = (LastRowWhite + 1);
							if (LastRowWhite == 8){
								LastRowWhite = 0;
								LastColWhite = 10;
							}
						}
						else{
							Pieces[ChessboardState[CurrentRow][CurrentCol]]->Move(CalculateCoordinates(LastRowBlack, LastColBlack));
							
							CemeteryState[LastRowBlack][LastColBlack + 3] = ChessboardState[CurrentRow][CurrentCol];
							LastRowBlack = (LastRowBlack - 1);
							if (LastRowBlack == -1){
								LastRowBlack = 7;
								LastColBlack = -3;
							}
						}
					}
					if (ChessboardState[CurrentRow][CurrentCol].find("King") != string::npos){
						win = true;
					}
					ChessboardState[CurrentRow][CurrentCol] = PieceSelected;

					if ((PieceSelected.find("Pawn") != string::npos) && (PieceSelected.find("white") != string::npos) && (CurrentRow == 7)){
						CurrentTurnState = RESCUE;
						LastRowPawn = CurrentRow;
						LastColPawn = CurrentCol;
					}
					else if ((PieceSelected.find("Pawn") != string::npos) && (PieceSelected.find("black") != string::npos) && (CurrentRow == 0)){
						CurrentTurnState = RESCUE;
						LastRowPawn = CurrentRow;
						LastColPawn = CurrentCol;
					}
					else if (win){
						CurrentTurnState = WIN;
					}
					else{
						CurrentTurnState = SELECTION;
						if ((CurrentRow != InitRowPieceSelected) || (CurrentCol != InitColPieceSelected)){
							if (CurrentTurn == TURN_BLACK){
								CurrentTurn = TURN_WHITE;
								MyCamera->updateCamera(glm::vec3(-10.0f, 9.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f);
							}
							else{
								CurrentTurn = TURN_BLACK;
								MyCamera->updateCamera(glm::vec3(10.0f, 9.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -135.0f);
							}
						}
					}
				}
				else{
					SoundEngine->play2D("audio/doh.mp3",GL_FALSE);
				}
				clicked = false;
			}

		
			for (int i = 0; i < 8; ++i){
				for (int j = 0; j < 8; ++j){
					if (MovesAvaible[i][j] != NULL){
						MovesAvaible[i][j]->Render(CalculateCoordinates(i,j));
					}
				}
			}
		
			break;
		case RESCUE:
			if (((p.x >(-LENGTH_CHESSBOARD / 2)) && (p.x < (LENGTH_CHESSBOARD / 2) &&
				(p.z < -LENGTH_CELL * 5) && (p.z >(-LENGTH_CELL * 7)))) ||
				((p.x >(-LENGTH_CHESSBOARD / 2)) && (p.x < (LENGTH_CHESSBOARD / 2) &&
				(p.z > LENGTH_CELL * 5) && (p.z < (LENGTH_CELL * 7))))){
				CalculateCell(p);
			}
			Selection->Render(CalculateCoordinates(CurrentRow, CurrentCol));
				if (clicked == true){
					if ((CurrentTurn == TURN_WHITE) && ((CurrentCol == 9) || (CurrentCol == 10))){
						if (CemeteryState[CurrentRow][CurrentCol - 7].find("white") != string::npos){
							Pieces[PieceSelected]->Move(CalculateCoordinates(CurrentRow, CurrentCol));
							Pieces[CemeteryState[CurrentRow][CurrentCol - 7]]->Move(CalculateCoordinates(LastRowPawn, LastColPawn));
							ChessboardState[LastRowPawn][LastColPawn] = CemeteryState[CurrentRow][CurrentCol - 7];
							CemeteryState[CurrentRow][CurrentCol - 7] = PieceSelected;

							CurrentTurnState = SELECTION;
							if (CurrentTurn == TURN_BLACK){
								CurrentTurn = TURN_WHITE;
								MyCamera->updateCamera(glm::vec3(-10.0f, 9.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f);
							}
							else{
								CurrentTurn = TURN_BLACK;
								MyCamera->updateCamera(glm::vec3(10.0f, 9.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -135.0f);
							}
						}
					}
					if ((CurrentTurn == TURN_BLACK) && ((CurrentCol == -3) || (CurrentCol == -2))){
						if (CemeteryState[CurrentRow][CurrentCol + 3].find("black") != string::npos){
							Pieces[PieceSelected]->Move(CalculateCoordinates(CurrentRow, CurrentCol));
							Pieces[CemeteryState[CurrentRow][CurrentCol + 3]]->Move(CalculateCoordinates(LastRowPawn, LastColPawn));
							ChessboardState[LastRowPawn][LastColPawn] = CemeteryState[CurrentRow][CurrentCol + 3];
							CemeteryState[CurrentRow][CurrentCol + 3] = PieceSelected;

							CurrentTurnState = SELECTION;
							if (CurrentTurn == TURN_BLACK){
								CurrentTurn = TURN_WHITE;
								MyCamera->updateCamera(glm::vec3(-10.0f, 9.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f);
							}
							else{
								CurrentTurn = TURN_BLACK;
								MyCamera->updateCamera(glm::vec3(10.0f, 9.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -135.0f);
							}
						}
					}
					clicked = false;
			}

			break;
		case WIN:
			break;
	}
}

void ChessGame::CalculateMoves(string Moves[][8]){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			MovesAvaible[i][j] = NULL;
			if (Moves[i][j] != "cannot_pass"){
				MovesAvaible[i][j] = new Quad(Width, Height, MyCamera);
			}
		}
	}
}
glm::vec3 ChessGame::CalculateCoordinates(int row, int col){
	return glm::vec3((row * LENGTH_CELL) - (LENGTH_CHESSBOARD / 2) + (LENGTH_CELL / 2), 0.0f, (col * LENGTH_CELL) - (LENGTH_CHESSBOARD / 2) + (LENGTH_CELL / 2));
}

void ChessGame::CalculateCell(glm::vec3 p){
		int row, col;
		row = -1;
		for (float i = (-LENGTH_CELL * 4); p.x > i; i += LENGTH_CELL){
			row++;
		}
		col = -4;
		for (float i = (-LENGTH_CELL * 7); p.z > i; i += LENGTH_CELL){
			col++;
		}
		CurrentRow = row;
		CurrentCol = col;
}

bool ChessGame::IsWhite(string type){
	if ((type.find("white") != string::npos))
		return true;
	return false;
}

bool ChessGame::IsBlack(string type){
	if ((type.find("black") != string::npos))
		return true;
	return false;
}

bool ChessGame::AreThereMovesAvaible(){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; j++){
			if (Moves[i][j].find("can_pass") != string::npos || Moves[i][j].find("can_eat") != string::npos){
				return true;
			}
		}
	}
	return false;
}

glm::vec3 ChessGame::CalculateRay(){
	glm::mat4 view = MyCamera->getViewMatrix();
	glm::mat4 projection = glm::perspective(MyCamera->getZoom(), (float)Width / (float)Height, 0.1f, 1000.0f);

	float x = (2.0f * xpos) / Width - 1.0f;
	float y = 1.0f - (2.0f * ypos) / Height;
	float z = 1.0f;
	glm::vec3 ray_nds(x, y, z);
	glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
	glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
	glm::vec3 ray_wor = glm::vec3((glm::inverse(view) * ray_eye));
	ray_wor = glm::normalize(ray_wor);

	return ray_wor;
}

void ChessGame::RescuePiece(string Color){
	for (std::map<string, Piece*>::iterator it = Pieces.begin(); it != Pieces.end(); ++it){
		if ((it->first.find(Color) != string::npos) && (it->second->Ate)){

		}
	}
}



bool ChessGame::IsTurnWhite(){
	return (CurrentTurn == TURN_WHITE);
}
bool ChessGame::IsTurnBlack(){
	return (CurrentTurn == TURN_BLACK);
}
bool ChessGame::IsThereAWinner(){
	return (CurrentTurnState == WIN);
}