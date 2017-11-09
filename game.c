#include "helper.c"
#include "drawHelper.c"
#include "vec.c"
#include "room.c"

Room r;

void init(){
	Room_set(&r, 5, 5);
}

void onKey(int key){
	switch(key){
	case KEY_BACKSPACE:
		again=0;
		break;
	}
}

void draw(){
	Room_draw(r, 0, 0);
}
