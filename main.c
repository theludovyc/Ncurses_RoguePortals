#include <ncurses.h>

char again=1;

#include "game.c"

int main(){
	initscr();

	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	onInit();

	onDraw();

	refresh();
	
	do{
		onKey(wgetch(stdscr));

		erase();

		onDraw();

		refresh();
	}while(again);

	onExit();
	
	endwin();

	return 0;
}
