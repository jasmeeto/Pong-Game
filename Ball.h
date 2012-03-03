class Ball {
	int posx,posy,height,width,dirx,diry;

	public:

	Ball(){
		posx = 0;posy=0; height = width = 3; dirx =diry = -1;
	}

	int getX(){
		return posx;
	}
	int getY(){
		return posy;
	}

	int getWidth(){
		return width;
	}

	int getHeight(){
		return height;
	}
	int getDirX(){
		return dirx;
	}
	int getDirY(){
		return diry;
	}

	void setWidth(int iWidth){
		width = iWidth;
	}
	void setHeight(int iHeight){
		height = iHeight;
	}
	void setX(int X){
		posx=X;
	}
	void setY(int Y){
		posy = Y;
	}
	void setDirX(int dx){
		dirx = dx;
	}
	void setDirY(int dy){
		diry= dy;
	}

};
