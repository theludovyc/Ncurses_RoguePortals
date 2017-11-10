#include "helper.c"
#include "drawHelper.c"
#include "vec.cc"
#include "room.cc"
#include "entity.cc"
#include "portal.cc"

Room *r;

Entity *player;
Vec *playerDir;

Portal *ePortal;
Portal *wPortal;
Portal *nPortal;
Portal *sPortal;

void onInit(){
	r=new Room(5, 4, 5, 5);
	player=new Entity(7, 6, "player", '@');
	playerDir=new Vec();
	ePortal=new Portal(9, 6, "Est Portal");
	wPortal=new Portal(5, 6, "West Portal");
	nPortal=new Portal(7, 4, "North Portal");
	sPortal=new Portal(7, 8, "South Portal");
}

void checkCol_room(){
	if( (*r).isGround( *player+*playerDir ) ){
		(*player)+=(*playerDir);
	}
}

uchar checkCol_portal(Portal *p){
	if( (*p).isOpen() && ( *player+*playerDir == *p ) ){
		return 1;
	}
	return 0;
}

void checkCol_ePortal(){
	if( checkCol_portal(ePortal) ){
		(*player).addX(2);
		return;
	}

	checkCol_room();
}

void checkCol_wPortal(){
	if( checkCol_portal(wPortal) ){
		(*player).addX(-2);
		return;
	}

	checkCol_room();
}

void checkCol_nPortal(){
	if( checkCol_portal(nPortal) ){
	  (*player).addY(-2);
		(*r).setY(0);
		(*nPortal).close();
		(*sPortal).setY( (*nPortal).getY() );
		return;
	}

	checkCol_room();
}

void checkCol_sPortal(){
	if( checkCol_portal(sPortal) ){
		(*player).addY(2);
		return;
	}

	checkCol_room();
}

void onKey(int key){
	switch(key){
	case KEY_BACKSPACE:
		again=0;
		break;

	case KEY_RIGHT:
		(*playerDir).setXY(1, 0);
		checkCol_ePortal();
		break;

	case KEY_LEFT:
		(*playerDir).setXY(-1, 0);
		checkCol_wPortal();
		break;

	case KEY_UP:
		(*playerDir).setXY(0, -1);
		checkCol_nPortal();
		break;

	case KEY_DOWN:
	  (*playerDir).setXY(0, 1);
		checkCol_sPortal();
		break;
	}
}

void onUpdate(){
	
}

void draw_portal(Portal *p){
	if( (*p).isOpen() ){
		(*p).draw();
	}
}

void onDraw(){
	(*r).draw();

	draw_portal(ePortal);
	draw_portal(wPortal);
	draw_portal(nPortal);
	draw_portal(sPortal);
	
	(*player).draw();
}

void onExit(){
}
