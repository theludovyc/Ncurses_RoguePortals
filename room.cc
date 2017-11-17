#define _Room

class Room:public Rect{
public:
	Room(uchar posX, uchar posY, uchar i, uchar j)
		:Rect(posX, posY, i, j){
	}

	//algorithme faux si plusieurs rooms active à la fois
	uchar isGround(uchar posX, uchar posY){
		if(posY==y || posX==x || posX==getR()-1 || posY==getB()-1){
			return 0;
		}
		return 1;
	}

	uchar isGround(Vec v){
		return isGround(v.x, v.y);
	}

	void draw(){
		uchar i,j;
		uchar c;

		for(j=0;j<h;j++){
			for(i=0;i<w;i++){
				if(j==0 || i==0 || i==w-1 || j==h-1){
					c='#';
				}else{
					c='.';
				}
			
				drawChar(x+i, y+j, c);
			}
		}
	}
};

