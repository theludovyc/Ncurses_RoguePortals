class Portal:public Entity{
protected:
	uchar myOpen;

public:
	Portal(uchar posX, uchar posY, const char *n)
		:Entity(posX, posY, n, 'O'){
		myOpen=1;
	}

	void close(){
		if( myOpen!=0 ){
			myOpen=0;
		}
	}

	void open(){
		if( myOpen!=1 ){
			myOpen=1;
		}
	}

	uchar isOpen(){
		if(myOpen){
			return 1;
		}
		return 0;
	}
};
