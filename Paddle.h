class Paddle {
	int posx,posy,height,width;

	public:
	static int count;

	Paddle(){
		posx=0,posy=0,height =10 , width = 2;
		count++;
		}

	~Paddle() {
		count--;
		}

	int howMany(){
		return count;
	}

	void setSize(int iWidth, int iHeight){
		height = iHeight;
		width = iWidth;
	}

	void setX(int x){
		posx= x;
	}
	void setY(int y){
		posy=y;
	}

	int getX(){
		return posx;
	}
	int getY(){
		return posy;
	}
	int getHeight(){
		return height;
	}
	int getWidth(){
		return width;
	}

	void initCount(){
		count = 0;
	}

};
