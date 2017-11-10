#define _Entity

#ifndef _Vec
#include "vec.cc"
#endif

class Entity:public Vec{
protected:
	const char *name;
	unsigned char symbol;
	
public:
	Entity()
		:Vec(){
	}

	Entity(const char *n, unsigned char c)
		:Vec(0,0){
		name=n;
		symbol=c;
	}

	Entity(unsigned char posX, unsigned char posY, const char *n, unsigned char c)
		:Vec(posX, posY){
		name=n;
		symbol=c;
	}

	~Entity(){
	}

	void draw(){
		drawChar(x, y, symbol);
	}
};
