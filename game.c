#include "helper.c"
#include "drawHelper.c"
#include "vec.cc"
#include "room.cc"
#include "entity.cc"

Room *r;
Entity *player;
Vec *playerDir;
Entity *nPortal;

void onInit(){
	r=new Room(5, 4, 5, 5);
	player=new Entity(7, 6, "player", '@');
	playerDir=new Vec();
	nPortal=new Entity(7, 4, "North Portal", 'O');
}

void onKey(int key){
	switch(key){
	case KEY_BACKSPACE:
		again=0;
		break;

	case KEY_RIGHT:
		(*playerDir).setXY(1, 0);
		break;

	case KEY_LEFT:
		(*playerDir).setXY(-1, 0);
		break;

	case KEY_UP:
		(*playerDir).setXY(0, -1);
		break;

	case KEY_DOWN:
	  (*playerDir).setXY(0, 1);
		break;
	}
}

void onUpdate(){
	if( (*r).isGround( *player+*playerDir ) ){
		(*player)+=(*playerDir);
	}
}

void onDraw(){
	(*r).draw();
	(*player).draw();
	(*nPortal).draw();
}

void onExit(){
}
