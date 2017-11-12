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

void gen_portalPosY(Portal *p){
	if( (*r).getHeight()>3 ){
		(*p).setY( rand_between( (*r).getY()+1, (*r).getY()+(*r).getHeight()-2 ) );
	}else{
		(*p).setY( (*r).getY()+1 );
	}
}

void gen_portalE(){
	if( (*r).getX()+(*r).getLength() < mapLength ){
		(*ePortal).open();
		(*ePortal).setX( (*r).getX()+(*r).getLength()-1 );

		gen_portalPosY(ePortal);
	}else{
		(*ePortal).close();
	}
}

void gen_portalW(){
	if( (*r).getX()>1 ){
		(*wPortal).open();
		(*wPortal).setX( (*r).getX() );

		gen_portalPosY(wPortal);
	}else{
		(*wPortal).close();
	}
}

void gen_portalPosX(Portal *p){
	if( (*r).getLength() >3 ){
		(*p).setX( rand_between( (*r).getX()+1, (*r).getX()+(*r).getLength()-2 ) );
	}else{
		(*p).setX( (*r).getX()+1 );
	}
}

void gen_portalN(){
	if( (*r).getY()>1 ){
		(*nPortal).open();
		(*nPortal).setY( (*r).getY() );

		gen_portalPosX(nPortal);
	}else{
		(*nPortal).close();
	}
}

void gen_portalS(){
	if( (*r).getY()+(*r).getHeight() < mapHeight ){
		(*sPortal).open();
		(*sPortal).setY( (*r).getY()+(*r).getHeight()-1 );

		gen_portalPosX(sPortal);
	}else{
		(*sPortal).close();
	}
}

void gen_roomSetHeight(Portal p){
	(*r).setY( rand_between(0, p.getY()-1 ) );

	(*r).setHeight( rand_between( p.getY()+2-(*r).getY(), mapHeight+1-(*r).getY() ) );
}

void gen_roomE(){
	(*wPortal).open();
	(*wPortal).setXY(*ePortal);

	(*r).setX( (*wPortal).getX() );

	(*r).setLength(3);

	if( (*r).getX()+(*r).getLength() < mapLength ){
		(*r).setLength( rand_between(3, mapLength-(*r).getX()+1 ) );
	}

  gen_roomSetHeight( *wPortal );

	gen_portalE();
	gen_portalN();
	gen_portalS();
}

void gen_roomW(){
	(*ePortal).open();
	(*ePortal).setXY(*wPortal);

	(*r).setX( (*ePortal).getX()-2 );

	if( (*r).getX()!=0 ){
		(*r).setX( rand_between(0, (*r).getX() ) );
	}

	(*r).setLength( (*ePortal).getX()-(*r).getX() +1 );

  gen_roomSetHeight( *ePortal );

	gen_portalW();
	gen_portalN();
	gen_portalS();
}

void gen_roomLength(Portal p){
	(*r).setX( rand_between(0, p.getX()-1 ) );

	(*r).setLength( rand_between( p.getX()+2-(*r).getX(), mapLength+1-(*r).getX() ) );
}

void gen_roomN(){
	(*sPortal).open();
	(*sPortal).setXY(*nPortal);

	(*r).setY( (*sPortal).getY()-2 );

	if( (*r).getY()!=0 ){
		(*r).setY( rand_between(0, (*r).getY() ) );
	}
		
	(*r).setHeight( (*sPortal).getY()-(*r).getY()+1 );

	gen_roomLength(*sPortal);

	gen_portalN();
	gen_portalE();
	gen_portalW();
}

void gen_roomS(){
	(*nPortal).open();
	(*nPortal).setXY(*sPortal);

	(*r).setY( (*nPortal).getY() );

	(*r).setHeight(3);

	if( (*r).getY()+(*r).getHeight() < mapHeight ){
		(*r).setHeight( rand_between(3, mapHeight-(*r).getY()+1 ) );
	}

	gen_roomLength(*nPortal);

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
