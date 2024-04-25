#include <ncurses.h>
#include "tetrisBoard.h"

TetrisBoard::TetrisBoard(int winX, int winY)
{	
	win = newwin(BOARD_HEIGHT*TILE_HEIGHT+2,BOARD_WIDTH*TILE_WIDTH+2,winY,winX);
	for(int x = 0; x < BOARD_WIDTH; x++)
	{
        	for(int y = 0; y < BOARD_HEIGHT; y++)
		{
			tiles[x][y] = 0;
        	}
    	}
	refresh();
	wclear(win);
	box(win,0,0);
	wrefresh(win);
}
int TetrisBoard::GetTile(const Coord &coord) const
{
	if(coord.x<0 || coord.y<-TOP_SPACE || coord.x>=BOARD_WIDTH || coord.y>=BOARD_HEIGHT) return 1;
	if(coord.y<0) return 0;
	return tiles[coord.x][coord.y];
}
void TetrisBoard::SetTile(const Coord &coord, const int &value)
{
	if(coord.x<0 || coord.y<0 || coord.x>=BOARD_WIDTH || coord.y>=BOARD_HEIGHT) return;
	tiles[coord.x][coord.y] = value;
}
bool TetrisBoard::CheckTetromino(const Coord &coord,const Tetromino &tetromino)
{
	for(int x = 0; x < 4; x++)
    {
		for(int y = 0; y < 4; y++)
		{
			if(tetromino.GetTile(Coord(x,y))>0)
			{
                if(GetTile(Coord(coord.x+x,coord.y+y))>0) return false;
        	}
		}
	}	
	return true;
}
void TetrisBoard::DrawTetromino(const Coord &coord,const Tetromino &tetromino)
{
	for(int x = 0; x < 4; x++)
	{
        for(int y = 0; y < 4; y++)
		{
			if(coord.y+y>=0)
			{
				int color = tetromino.GetTile(Coord(x,y));
				if(color>0) DrawTile(Coord(x,y)+coord,color);
			}
		}
    }
	wrefresh(win);
}
void TetrisBoard::PlaceTetromino(const Coord &coord,const Tetromino &tetromino)
{
	for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 4; y++)
        {	
			int value = tetromino.GetTile(Coord(x,y));
			if(value>0)
			{
				SetTile(Coord(coord.x+x,coord.y+y),value);
			}
        }
	}
}
int TetrisBoard::ClearLines()
{
	int numLines = 0;
        for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		bool clear = true;
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			if(tiles[x][y]<=0)
			{
				clear = false;
				break;
			}		
		}
		if(clear)
		{
			for(int x = 0; x < BOARD_WIDTH; x++)
			{
				tiles[x][y] = 0;
                        }
			for(int j = y; j > 0; j--)
			{
				for(int x = 0; x < BOARD_WIDTH; x++)
                        	{
                	                tiles[x][j] = tiles[x][j-1];
        	                }
			}
			numLines++;
                }
	}
	return numLines;
}
void TetrisBoard::DrawTiles()
{
	for(int x = 0; x < BOARD_WIDTH; x++)
	{
		for(int y = 0; y < BOARD_HEIGHT; y++)
		{
			int color = tiles[x][y];
			DrawTile(Coord(x,y),color);
		}
	}
	wrefresh(win);
}
void TetrisBoard::DrawTile(const Coord &coord, const int &color)
{
	wattron(win,COLOR_PAIR(color));
        for(int x = 0; x < TILE_WIDTH; x++)
        {
                for(int y = 0; y < TILE_HEIGHT; y++)
                {
       			mvwaddch(win,coord.y*TILE_HEIGHT+y+1,coord.x*TILE_WIDTH+x+1,' ');
		}
	}
     	wattroff(win,COLOR_PAIR(color));
}
