#include "tetromino.h"

Tetromino::Tetromino()
{

}
Tetromino::Tetromino(int piece)
{
	int patterns[7][16] = {
                                        {0,1,0,0,
                                        0,1,0,0,
                                        0,1,0,0,
                                        0,1,0,0},

                                        {0,2,2,0,
                                        0,2,2,0,
                                        0,0,0,0,
                                        0,0,0,0},

                                        {0,0,0,0,
                                        3,3,3,0,
                                        0,3,0,0,
                                        0,0,0,0},

                                        {0,4,4,0,
                                        4,4,0,0,
                                        0,0,0,0,
                                        0,0,0,0},

                                        {5,5,0,0,
                                        0,5,5,0,
                                        0,0,0,0,
                                        0,0,0,0},

                                        {0,6,0,0,
                                        0,6,0,0,
                                        6,6,0,0,
                                        0,0,0,0},

                                        {0,7,0,0,
                                        0,7,0,0,
                                        0,7,7,0,
                                        0,0,0,0}};

	this->piece = piece;
	rotation = 0;
    	for(int i = 0; i < 16; i++)
	{
            tiles[i%4][i/4] = patterns[piece][i];
    	}
}
int Tetromino::GetTile(const Coord &coord) const
{
	if(coord.x<0 || coord.y<0 || coord.x>=4 || coord.y>=4) return 0;
	return tiles[coord.x][coord.y];
}
int Tetromino::GetPiece(){
	return piece;
}
void Tetromino::RotateClockwise()
{
	Coord shifts[7][4] = {{Coord(1,0),Coord(1,0),Coord(1,0),Coord(1,0)},
						{Coord(0,-1),Coord(0,-1),Coord(0,-1),Coord(0,-1)},
						{Coord(0,0),Coord(0,0),Coord(0,0),Coord(0,0)},
						{Coord(0,0),Coord(0,0),Coord(0,0),Coord(0,0)},
						{Coord(0,0),Coord(0,0),Coord(0,0),Coord(0,0)},
						{Coord(0,0),Coord(0,0),Coord(0,0),Coord(0,0)},
						{Coord(0,0),Coord(0,0),Coord(0,0),Coord(0,0)}};
	int newTiles[4][4];
	for(int i = 0; i < 16; i++)
	{
            newTiles[i%4][i/4] = 0;
    }
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			Coord aroundPivot = Coord(x,y) - Coord(1,1);
			Coord newPivotCoord = Coord(-aroundPivot.y,aroundPivot.x);
			Coord newCoord = newPivotCoord + Coord(1,1) + shifts[piece][rotation];
			if(newCoord.x<0 || newCoord.y<0 || newCoord.x>=4 || newCoord.y>=4) continue;
			newTiles[newCoord.x][newCoord.y] = tiles[x][y];
		}
	}
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			tiles[x][y] = newTiles[x][y];
		}
	}
	rotation = (rotation+1)%4;
}
void Tetromino::Rotate(bool direction)
{
	if(direction){
		RotateClockwise();
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			RotateClockwise();
		}
		
	}
}

