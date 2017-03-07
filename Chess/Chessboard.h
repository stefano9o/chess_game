
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include "Model.h"


class Chessboard{
public:
	Chessboard(GLchar* path);
	~Chessboard();

	void Draw(Shader shader);
private:
	Model *MyModel;
};

#endif