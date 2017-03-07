
#ifndef CHESSGAME_H
#define CHESSGAME_H

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <irrklang/irrKlang.h>
using namespace irrklang;


#include "Piece.h"
#include "PiecePawn.h"
#include "PieceRock.h"
#include "PieceKnight.h"
#include "PieceBishop.h"
#include "PieceQueen.h"
#include "PieceKing.h"
#include "Shader.h"
#include "Chessboard.h"
#include "Quad.h"
#include "Camera.h"

#define LENGTH_CHESSBOARD (1.797 * 5)
#define LENGTH_CELL (LENGTH_CHESSBOARD / 8)

enum Turn{
	TURN_WHITE,
	TURN_BLACK
};

enum TurnState{
	SELECTION,
	MOVEMENT,
	RESCUE,
	WIN
};

class ChessGame{
public:
	ChessGame(int Width, int Height, Camera *MyCamera, ISoundEngine *SoundEngine);
	~ChessGame(); 

	void Init();
	void Draw(Shader shader);

	int xpos, ypos;
	bool clicked;
	bool IsTurnWhite();
	bool IsTurnBlack();
	bool IsThereAWinner();
private:
	int Width, Height;
	Camera *MyCamera;
	Quad *Selection;
	ISoundEngine *SoundEngine;

	std::map<string, Piece*> Pieces;
	Chessboard *MyChessboard;
	
	string ChessboardState[8][8];
	string CemeteryState[8][4];
	Quad *MovesAvaible[8][8];
	string Moves[8][8];

	Turn CurrentTurn;
	TurnState CurrentTurnState;
	
	int CurrentRow, CurrentCol;

	string PieceSelected;
	int InitRowPieceSelected;
	int InitColPieceSelected;
	
	bool IsWhite(string type);
	bool IsBlack(string type);

	glm::vec3 CalculateCoordinates(int row, int col);
	glm::vec3 CalculateRay();
	void CalculateCell(glm::vec3 p);
	void ChessGame::CalculateMoves(string Moves[][8]);

	bool AreThereMovesAvaible();
	void RescuePiece(string Color);
};

#endif
