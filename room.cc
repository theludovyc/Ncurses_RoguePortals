#define _Room

#ifndef _Vec
#include "vec.cc"
#endif

class Room:public Vec{
 protected:
	uchar roomL;
	uchar roomH;

 public:
 Room(uchar posX, uchar posY, uchar rL, uchar rH)
	 :Vec(posX, posY){
		roomL=rL;
		roomH=rH;
	}

	//algorithme faux si plusieurs rooms
	uchar isGround(uchar posX, uchar posY){
		if(posY==y || posX==x || posX==x+roomL-1 || posY==y+roomH-1){
			return 0;
		}
		return 1;
	}

	uchar isGround(Vec v){
		return isGround(v.getX(), v.getY());
	}

	void draw(){
		uchar i,j;
		uchar c;

		for(j=0;j<roomH;j++){
			for(i=0;i<roomL;i++){
				if(j==0 || i==0 || i==roomL-1 || j==roomH-1){
					c='#';
				}else{
					c='.';
				}
			
				drawChar(x+i, y+j, c);
			}
		}
	}
};

