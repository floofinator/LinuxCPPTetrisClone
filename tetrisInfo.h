#ifndef TETRIS_INFO_H
#define TETRIS_INFO_H

#include <ncurses.h>
#include <list>
#include "coord.h"
#include "tetromino.h"

using namespace std;

class TetrisInfo
{
private:
	WINDOW *nextWin,*holdWin,*scoreWin;
	void DrawTile(const Coord &coord, const int &color, WINDOW *win);
	void DrawTetromino(const Coord &coord, const Tetromino &tetromino, WINDOW *win);
public:
	TetrisInfo(int winX, int winY);
	void DisplayNext(list<int> next);
	void DisplayHold(const int &hold);
	void DisplayNumLines(const int &lines);
};

#endif
