#include "helper.c"
#include "drawHelper.c"
#include "vec.cc"
#include "room.cc"
#include "entity.cc"

Room *r;
Entity *player;

void onInit(){
	r=new Room(5, 5, 5, 5);
	player=new Entity(6, 6, "player", '@');
}

void onKey(int key){
	switch(key){
	case KEY_BACKSPACE:
		again=0;
		break;

	case KEY_RIGHT:
		if( (*r).isGround( (*player)+Vec(1,0) ) ){
			(*player).addX(1);
		}
		break;

	case KEY_LEFT:
		if( (*r).isGround( (*player)+Vec(-1,0) ) ){
			(*player).addX(-1);
		}
		break;

	case KEY_UP:
		if( (*r).isGround( (*player)+Vec(0,-1) ) ){
			(*player).addY(-1);
		}
		break;

	case KEY_DOWN:
		if( (*r).isGround( (*player)+Vec(0, 1) ) ){
			(*player).addY(1);
		}
		break;
	}
}

void onDraw(){
	(*r).draw();
	(*player).draw();
}

void onExit(){
}
