#include <ncurses.h>

char again=1;

#include "game.c"

int main(){
	initscr();

	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	init();

	draw();

	refresh();
	
	do{
		onKey(wgetch(stdscr));

		erase();

		draw();

		refresh();
	}while(again);
	
	endwin();

	return 0;
}
