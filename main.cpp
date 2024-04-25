#include <ncurses.h>
#include <unistd.h>
#include "tetris.h"

#define DELAY 50000

int main()
{		
	initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
	nodelay(stdscr, TRUE);

	Tetris tetris;

	int ch;

	bool playing = true;

	while(playing){
		
		ch = getch();
		playing = ch != 'q';
	
		if(ch == KEY_LEFT) tetris.Move(Coord(-1,0));
		if(ch == KEY_RIGHT) tetris.Move(Coord(1,0));
		if(ch == KEY_DOWN) tetris.Move(Coord(0,1));
		if(ch == KEY_UP) tetris.Hold();
		if(ch == 'c') tetris.Rotate(true);
		if(ch == 'x') tetris.Rotate(false);
		if(ch == ' ') tetris.Drop();

		playing = tetris.Update() && playing;
		tetris.Draw();
		refresh();
		usleep(DELAY);
	}
	
	endwin();

	return 0;
}
