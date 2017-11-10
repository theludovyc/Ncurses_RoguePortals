#include "helper.c"
#include "drawHelper.c"
#include "vec.cc"
#include "room.c"
#include "entity.cc"

Room r;
Entity *player;

void init(){
	Room_set(&r, 5, 5);
	player=new Entity(5, 5, "player", '@');
}

void onKey(int key){
	switch(key){
	case KEY_BACKSPACE:
		again=0;
		break;

	case KEY_RIGHT:
		if(Room_isGround(r, (*player).getX()+1, (*player).getY() ) ){
			(*player).addX(1);
		}
		break;

	case KEY_LEFT:
		(*player).addX(-1);
		break;

	case KEY_UP:
		(*player).addY(-1);
		break;

	case KEY_DOWN:
		(*player).addY(1);
		break;
	}
}

void draw(){
	Room_draw(r, 5, 5);
	(*player).draw();
}
