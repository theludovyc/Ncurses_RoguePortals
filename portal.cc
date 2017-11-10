class Portal:public Entity{
protected:
	uchar myOpen;

public:
	Portal(uchar posX, uchar posY, const char *n)
		:Entity(posX, posY, n, 'O'){
		myOpen=1;
	}

	void close(){
		myOpen=0;
	}

	void open(){
		myOpen=1;
	}

	uchar isOpen(){
		if(myOpen){
			return 1;
		}
		return 0;
	}
};
