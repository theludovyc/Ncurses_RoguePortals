#ifndef _Time
#include <time.h>
#define _Time
#endif

#include "helper.c"
#include "drawHelper.c"
#include "vec.cc"
#include "room.cc"
#include "entity.cc"
#include "portal.cc"

uchar mapLength;
uchar mapHeight;

Room *r;

Entity *player;
Vec *playerDir;

Portal *ePortal;
Portal *wPortal;
Portal *nPortal;
Portal *sPortal;

void onInit(){
	srand(time(null));

	mapLength=12;
	mapHeight=12;
	
	r=new Room(4, 4, 5, 5);
	
	player=new Entity(6, 6, "player", '@');
	playerDir=new Vec();
	
	ePortal=new Portal(8, 6, "Est Portal");
	wPortal=new Portal(4, 6, "West Portal");
	nPortal=new Portal(6, 4, "North Portal");
	sPortal=new Portal(6, 8, "South Portal");
}

void gen_portalE(){
	if( (*r).getX()+(*r).getLength() < mapLength ){
		(*ePortal).open();
		(*ePortal).setX( (*r).getX()+(*r).getLength()-1 );
	}else{
		(*ePortal).close();
	}
}

void gen_portalW(){
	if( (*r).getX()>1 ){
		(*wPortal).open();
		(*wPortal).setX( (*r).getX() );
	}else{
		(*wPortal).close();
	}
}

void gen_portalN(){
	if( (*r).getY()>1 ){
		(*nPortal).open();
		(*nPortal).setY( (*r).getY() );
	}else{
		(*nPortal).close();
	}
}

void gen_portalS(){
	if( (*r).getY()+(*r).getHeight() < mapHeight ){
		(*sPortal).open();
		(*sPortal).setY( (*r).getY()+(*r).getHeight()-1 );
	}else{
		(*sPortal).close();
	}
}


void gen_roomE(){
	(*wPortal).open();
	(*wPortal).setX( (*ePortal).getX() );

	(*r).setX( (*wPortal).getX() );

	(*r).setLength(3);

	if( (*r).getX()+(*r).getLength() < mapLength ){
		(*r).setLength( rand_between(3, mapLength-(*r).getX()+1 ) );
	}

	gen_portalE();
}

void gen_roomW(){
	(*ePortal).open();
	(*ePortal).setX( (*wPortal).getX() );

	(*r).setX( (*ePortal).getX()-2 );

	if( (*r).getX()!=0 ){
		(*r).setX( rand_between(0, (*r).getX() ) );
	}

	(*r).setLength( (*ePortal).getX()-(*r).getX() +1 );

	gen_portalW();
}

void gen_roomN(){
	(*sPortal).open();
	(*sPortal).setY( (*nPortal).getY() );

	(*r).setY( (*sPortal).getY()-2 );

	if( (*r).getY()!=0 ){
		(*r).setY( rand_between(0, (*r).getY() ) );
	}
		
	(*r).setHeight( (*sPortal).getY()-(*r).getY()+1 );

	gen_portalN();
}

void gen_roomS(){
	(*nPortal).open();
	(*nPortal).setY( (*sPortal).getY() );

	(*r).setY( (*nPortal).getY() );

	(*r).setHeight(3);

	if( (*r).getY()+(*r).getHeight() < mapHeight ){
		(*r).setHeight( rand_between(3, mapHeight-(*r).getY()+1 ) );
	}

	gen_portalS();
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
		gen_roomE();
		return;
	}

	checkCol_room();
}

void checkCol_wPortal(){
	if( checkCol_portal(wPortal) ){
		(*player).addX(-2);
		gen_roomW();
		return;
	}

	checkCol_room();
}

void checkCol_nPortal(){
	if( checkCol_portal(nPortal) ){
	  (*player).addY(-2);
	  gen_roomN();
		return;
	}

	checkCol_room();
}

void checkCol_sPortal(){
	if( checkCol_portal(sPortal) ){
		(*player).addY(2);
		gen_roomS();
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

	int i;
	char c;
	for(i=0;i<13;i++){
		if(i%4==0){
			c='X';
		}else{
			c='#';
		}

		mvaddch(0, i, c);
		mvaddch(i, 0, c);
		mvaddch(12, i, c);
		mvaddch(i, 12, c);
	}
}

void onExit(){
}
