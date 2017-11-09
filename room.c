struct Room{
	uchar roomL;
	uchar roomH;
};
typedef struct Room Room;

void Room_set(Room *r, uchar rL, uchar rH){
	(*r).roomL = rL;
	(*r).roomH = rH;
}

uchar Room_isGround(Room r, uchar x, uchar y){
	if(y==0 || x==0 || x==r.roomL-1 || y==r.roomH-1){
		return 0;
	}
	return 1;
}

void Room_draw(Room r, uchar posX, uchar posY){
	uchar i,j;
	uchar c;

	for(j=0;j<r.roomH;j++){
		for(i=0;i<r.roomL;i++){
			if(j==0 || i==0 || i==r.roomL-1 || j==r.roomH-1){
				c='#';
			}else{
				c='.';
			}
			
			drawChar(posX+i, posY+j, c);
		}
	}
}
