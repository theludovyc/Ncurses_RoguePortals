#define _Vec

class Vec{
protected:
	unsigned char x;
	unsigned char y;

public:
	Vec(){
		x=0;
		y=0;
	}

	Vec(unsigned char posX, unsigned char posY){
		x=posX;
		y=posY;
	}

	~Vec(){
	}

	void setXY(unsigned char posX, unsigned char posY){
		x=posX;
		y=posY;
	}

	void setX(unsigned char posX){
		x=posX;
	}

	void setY(unsigned char posY){
		y=posY;
	}

	void addXY(unsigned char posX, unsigned char posY){
		x+=posX;
		y+=posY;
	}

	void addX(unsigned char posX){
		x+=posX;
	}

	void addY(unsigned char posY){
		y+=posY;
	}
	
	unsigned char getX(){
		return x;
	}

	unsigned char getY(){
		return y;
	}

	Vec operator+ (Vec v){
		return Vec(x+v.x, y+v.y);
	}
};
