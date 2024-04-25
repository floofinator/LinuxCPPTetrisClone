#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <ncurses.h>
#include "coord.h"
#include "tetromino.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define TOP_SPACE 4
#define TILE_WIDTH 3
#define TILE_HEIGHT 2

class TetrisBoard
{
private:
	WINDOW *win;
	int tiles[BOARD_WIDTH][BOARD_HEIGHT];
	void DrawTile(const Coord &coord, const int &color);
public:
	int GetTile(const Coord &coord) const;
	void SetTile(const Coord &coord, const int &color);
	TetrisBoard(int winX,int winY);
	void DrawTetromino(const Coord &coord,const Tetromino &tetromino);
	bool CheckTetromino(const Coord &coord,const Tetromino &tetromino);
	void PlaceTetromino(const Coord &coord,const Tetromino &tetromino);
	int ClearLines();
	void DrawTiles();
};

#endif
