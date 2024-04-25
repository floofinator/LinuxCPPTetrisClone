#include "tetrisInfo.h"

#define NEXT_COUNT 3 
#define TILE_HEIGHT 1
#define TILE_WIDTH 2

using namespace std;

TetrisInfo::TetrisInfo(int winX, int winY)
{
	int width = 4*TILE_WIDTH+2;
	int position = winY;
	int height = NEXT_COUNT*4*TILE_HEIGHT+2;
	nextWin = newwin(height,width,position,winX);
	position += height;

	height = 4*TILE_HEIGHT+2;
	holdWin = newwin(height,width,position,winX);
	position += height;
	
	scoreWin = newwin(height,width,position,winX);
	
	refresh();

        wclear(nextWin);
	wclear(holdWin);
	wclear(scoreWin);

        box(nextWin,0,0);
	box(holdWin,0,0);
	box(scoreWin,0,0);

	mvwprintw(nextWin,0,2,"Next");
	mvwprintw(holdWin,0,2,"Hold");
	mvwprintw(scoreWin,0,2,"Lines");

        wrefresh(nextWin);
	wrefresh(holdWin);
	wrefresh(scoreWin);
}
void TetrisInfo::DisplayNext(list<int> next)
{	
	int pos = 0;
	for(list<int>::iterator it = next.begin(); it != next.end(); it++)
	{
		DrawTetromino(Coord(0,pos*4),Tetromino(*it),nextWin);
		pos++;
	}
}
void TetrisInfo::DisplayHold(const int &hold)
{
	DrawTetromino(Coord(0,0),Tetromino(hold),holdWin);
}
void TetrisInfo::DisplayNumLines(const int &lines)
{
	mvwprintw(scoreWin,2,2,"%d",lines);
	wrefresh(scoreWin);
}
void TetrisInfo::DrawTetromino(const Coord &coord,const Tetromino &tetromino, WINDOW *win)
{
        for(int x = 0; x < 4; x++)
        {
        	for(int y = 0; y < 4; y++)
                {
                        int color = tetromino.GetTile(Coord(x,y));
                	DrawTile(Coord(x,y)+coord,color,win);
                }
    	}
        wrefresh(win);
}
void TetrisInfo::DrawTile(const Coord &coord, const int &color, WINDOW *win)
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
