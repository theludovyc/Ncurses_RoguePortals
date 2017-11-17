#ifndef _Time
#include <time.h>
#define _Time
#endif

#define _Main

#include "helper.c"
#include "drawHelper.c"
#include "../MyLibCC/Geom/rect.cc"
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

void gen_portalPosY(Portal *p){
	if( (*r).w>3 ){
		(*p).y = rand_between( (*r).y+1, (*r).y+(*r).h-2 );
	}else{
		(*p).y = (*r).y+1;
	}
}

void gen_portalE(){
	if( (*r).x+(*r).w < mapLength ){
		(*ePortal).open();
		(*ePortal).x = (*r).x+(*r).w-1;

		gen_portalPosY(ePortal);
	}else{
		(*ePortal).close();
	}
}

void gen_portalW(){
	if( (*r).x>1 ){
		(*wPortal).open();
		(*wPortal).x = (*r).x;

		gen_portalPosY(wPortal);
	}else{
		(*wPortal).close();
	}
}

void gen_portalPosX(Portal *p){
	if( (*r).w >3 ){
		(*p).x = rand_between( (*r).x+1, (*r).x+(*r).w-2 );
	}else{
		(*p).x = (*r).x+1;
	}
}

void gen_portalN(){
	if( (*r).y>1 ){
		(*nPortal).open();
		(*nPortal).y = (*r).y;

		gen_portalPosX(nPortal);
	}else{
		(*nPortal).close();
	}
}

void gen_portalS(){
	if( (*r).y+(*r).h < mapHeight ){
		(*sPortal).open();
		(*sPortal).y = (*r).y+(*r).h-1;

		gen_portalPosX(sPortal);
	}else{
		(*sPortal).close();
	}
}

void gen_roomSetHeight(Portal p){
	(*r).y = rand_between(0, p.y-1 );

	(*r).h = rand_between( p.y+2-(*r).y, mapHeight+1-(*r).y );
}

void gen_roomE(){
	(*wPortal).open();
	(*wPortal).setXY(*ePortal);

	(*r).x = (*wPortal).x;

	(*r).w = 3;

	if( (*r).x+(*r).w < mapLength ){
		(*r).w = rand_between(3, mapLength-(*r).x+1 );
	}

  gen_roomSetHeight( *wPortal );

	gen_portalE();
	gen_portalN();
	gen_portalS();
}

void gen_roomW(){
	(*ePortal).open();
	(*ePortal).setXY(*wPortal);

	(*r).x = (*ePortal).x-2;

	if( (*r).x!=0 ){
		(*r).x = rand_between(0, (*r).x );
	}

	(*r).w = (*ePortal).x-(*r).x +1;

  gen_roomSetHeight( *ePortal );

	gen_portalW();
	gen_portalN();
	gen_portalS();
}

void gen_roomSetWidth(Portal p){
	(*r).x = rand_between(0, p.x-1 );

	(*r).w = rand_between( p.x+2-(*r).x, mapLength+1-(*r).x );
}

void gen_roomN(){
	(*sPortal).open();
	(*sPortal).setXY(*nPortal);

	(*r).y = (*sPortal).y-2;

	if( (*r).y!=0 ){
		(*r).y = rand_between(0, (*r).y );
	}
		
	(*r).h = (*sPortal).y-(*r).y+1;

	gen_roomSetWidth(*sPortal);

	gen_portalN();
	gen_portalE();
	gen_portalW();
}

void gen_roomS(){
	(*nPortal).open();
	(*nPortal).setXY(*sPortal);

	(*r).y = (*nPortal).y;

	(*r).h = 3;

	if( (*r).y+(*r).h < mapHeight ){
		(*r).h = rand_between(3, mapHeight-(*r).y+1 );
	}

	gen_roomSetWidth(*nPortal);

	gen_portalS();
	gen_portalE();
	gen_portalW();
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
		(*player).x+=2;
		gen_roomE();
		return;
	}

	checkCol_room();
}

void checkCol_wPortal(){
	if( checkCol_portal(wPortal) ){
		(*player).x-=2;
		gen_roomW();
		return;
	}

	checkCol_room();
}

void checkCol_nPortal(){
	if( checkCol_portal(nPortal) ){
	  (*player).y-=2;
	  gen_roomN();
		return;
	}

	checkCol_room();
}

void checkCol_sPortal(){
	if( checkCol_portal(sPortal) ){
		(*player).y+=2;
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
	int i;
	char c;
	for(i=0;i<13;i++){
		if(i%4==0){
			c='X';
		}else{
			c='+';
		}

		mvaddch(0, i, c);
		mvaddch(i, 0, c);
		mvaddch(12, i, c);
		mvaddch(i, 12, c);
	}
	
	(*r).draw();

	draw_portal(ePortal);
	draw_portal(wPortal);
	draw_portal(nPortal);
	draw_portal(sPortal);
	
	(*player).draw();
}

void onExit(){
}
