#include "tetris.h"

using namespace std;

Tetris::Tetris():board(0,0),info(32,0)
{
	start_color();
	init_pair(1,COLOR_BLACK,COLOR_CYAN);
	init_pair(2,COLOR_BLACK,COLOR_YELLOW);
	init_pair(3,COLOR_BLACK,COLOR_MAGENTA);
	init_pair(4,COLOR_BLACK,COLOR_GREEN);
	init_pair(5,COLOR_BLACK,COLOR_RED);
	init_pair(6,COLOR_BLACK,COLOR_BLUE);
	init_pair(7,COLOR_BLACK,COLOR_WHITE);
	
	willFall = willClearLines = true;

	nextPiece = -1;	

	fallTime = 8;
	fallProgress = 0;
	hold = -1;
	numLines = 0;
	
	info.DisplayNumLines(numLines);
	
	srand(time(NULL));

	for (int i = 0; i < 3; i++)
	{
		AddToBag();
	}
	
	NewTetromino();
}

bool Tetris::Update()
{
	fallProgress++;
	if(fallProgress>fallTime)
	{
		fallProgress = 0;
		if(willFall)
		{
			return Fall(1);
		}
		else
		{
			return true;
		}
	}
	return true;
}
bool Tetris::Fall(const int &steps){
	for(int i = 0; i < steps; i++){
		if(!Move(Coord(0,1))){
            board.PlaceTetromino(tetrominoCoord,currentTetromino);
			if(willClearLines)
			{
				numLines += board.ClearLines();
				info.DisplayNumLines(numLines);
			}
			return NewTetromino();
        	}
	}
        return true;	
}
bool Tetris::NewTetromino()
{
	tetrominoCoord = Coord(4,-2);
	currentTetromino = Tetromino(TakeFromBag());
	return TetrominoFits();
}
bool Tetris::Move(const Coord &direction)
{
	tetrominoCoord += direction;
	if(!TetrominoFits()){
		tetrominoCoord -= direction;	
		return false;
	}
	return true;
}
bool Tetris::Rotate(bool direction)
{
	currentTetromino.Rotate(direction);
	if(TetrominoFits())
	{
		return true;
	}
	else
	{
		for(int y = 0; y <= 4; y++)
		{
			for(int x = 0; x <= 4; x++)
			{
				int xPos = x;
				if(xPos>2) xPos=-(xPos-2);
				int yPos = y;
				if(yPos>2) yPos=-(yPos-2);
				if(Move(Coord(xPos,yPos)))
				{
					return true;
				}
			}
		}
	}	
	return false;
}
void Tetris::Drop()
{
	Fall(BOARD_HEIGHT);
}
void Tetris::Hold()
{
	if(hold>=0){
		int newHold = currentTetromino.GetPiece();
		currentTetromino = Tetromino(hold);
		hold = newHold;
		tetrominoCoord = Coord(4,-2);
	}else{
		hold = currentTetromino.GetPiece();
		NewTetromino();
	}
	info.DisplayHold(hold);
}
bool Tetris::TetrominoFits()
{
	return board.CheckTetromino(tetrominoCoord,currentTetromino);
}
void Tetris::Draw()
{
	board.DrawTiles();
	board.DrawTetromino(tetrominoCoord,currentTetromino);
	
	int pos = 0;	
	for(list<int>::iterator it = bag.begin(); it != bag.end(); it++)
	{
		board.DrawTetromino(Coord(12,pos*4),Tetromino(*it));
		pos++;
	}
}

void Tetris::AddToBag()
{
	if(nextPiece<0 || nextPiece>6)
	{
		bool present = true;
		int newIndex = 0;
		int attempts = 0;
		while (present && attempts<7)
		{
			present = false;
			newIndex =  rand() % 7;
			for (list<int>::iterator it = bag.begin(); it != bag.end(); it++)
			{
				if(*it == newIndex)
				{
					present = true;
					break;
				}
			}
			attempts++;
		}
		bag.push_back(newIndex);
	}else{
		bag.push_back(nextPiece);
	}
	info.DisplayNext(bag);
}

int Tetris::TakeFromBag()
{
	int index = bag.front();
	bag.pop_front();
	AddToBag();
	return index;
}
int Tetris::GetNumLines()
{
	return numLines;
}
