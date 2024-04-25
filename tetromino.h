#ifndef TETROMINO_H
#define TETROMINO_H

#include "coord.h"

class Tetromino{
    	int tiles[4][4];
	int piece,rotation;
	void RotateClockwise();
public:
	Tetromino();
	Tetromino(int piece);
	int GetPiece();
	int GetTile(const Coord &coord) const;
	void Rotate(bool direction);
};

#endif //TETROMINO_H
