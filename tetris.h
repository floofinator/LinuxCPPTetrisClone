#ifndef TETRIS_H
#define TETRIS_H

#include "tetrisBoard.h"
#include <list>
#include <stdlib.h>
#include <time.h>
#include "tetrisInfo.h"

class Tetris
{
private:
	TetrisBoard board;
	TetrisInfo info;
	Coord tetrominoCoord;
	int hold,fallProgress,numLines;
	std::list<int> bag, history;
	Tetromino currentTetromino;
	bool TetrominoFits();
	bool NewTetromino();
	bool Fall(const int &steps);
	void AddToBag();
	int TakeFromBag();
public:
	Tetris();
	bool willFall,willClearLines;
	int fallTime,nextPiece;
	int GetNumLines();
	bool Move(const Coord &direction);
	bool Rotate(bool direction);
	void Drop();
	void Hold();
	bool Update();
	void Draw();
};

#endif //TETRIS_H
