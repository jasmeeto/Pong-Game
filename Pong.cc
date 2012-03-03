#include <allegro.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include "Paddle.h"
#include "Ball.h"

using namespace std;

//const int scrx=640,scry=480;
#define scrx 800
#define scry 600

int score1=0,score2=0;

volatile int aftResult=0;

volatile bool closeWindow= false;
void CloseButtonCallBack(){closeWindow = true;}
END_OF_FUNCTION(CloseButtonCallBack);

volatile long ticks = 0;
void Increment(){ticks++;}
END_OF_FUNCTION(Increment);

int Paddle::count = 0;


void DrawPaddle(Paddle& p,BITMAP* Buffer){
	rectfill (Buffer, p.getX(),p.getY(),p.getX() + p.getWidth(),p.getY()+p.getHeight(), makecol(255,255,0));
}

void DrawBall(Ball& b,BITMAP* Buffer){
	circlefill (Buffer, b.getX(),b.getY(),b.getWidth()/2, makecol(0,255,255));
}

void DrawLine(BITMAP* Buffer){
	int i=0,j=20;
	while(j<=scry){
		rectfill (Buffer, scrx/2-3,i,scrx/2+3,j, makecol(100,100,100));
		i=j+3;
		j=i+20;
	}
}
void StartScreen(BITMAP * bmp){
//coming soon
}

void resetBall(Ball& b){
	b.setX(scrx/2);
	b.setY(scry/2);
	srand(time(0));
	//int yloc= (rand()%scry)+1,
	int dirx =(rand()%2)+1, diry = (rand()%2)+1;
	dirx=(dirx==1)?-1:1;
	diry=(diry==1)?-1:1;
	b.setDirX(dirx);
	b.setDirY(diry);
	aftResult=1;
}

void resetBall(Ball& b,Paddle p,int n){
	if (n==1){
		b.setX(p.getX()+p.getWidth()+b.getWidth()/2);
		b.setY(p.getY()+p.getHeight()/2);
		b.setDirX(1);
		score2++;
	}else{
		b.setX(p.getX()-b.getWidth()/2);
		b.setY(p.getY()+p.getHeight()/2);
		b.setDirX(-1);
		score1++;
	}
	if (score1==2 && score2 >=2 || score1>=2 && score2==2 ){
		allegro_message("Time to speed Things up!");
	}
	if(score1== 11 || score2 ==11){
		allegro_message(score1==11?"Player 1 is the Winner":"Player 2 is the Winner");
		score1=score2=0;
	}

	aftResult=1;
}

void moveBall(Ball& b,Paddle& p1, Paddle& p2){
	int movespeed=4;
	if (score1>=2 && score2 >=2	|| key[KEY_I]){
		movespeed++;
	}

	int dirx = b.getDirX(),diry =b.getDirY();
	int bx= b.getX(),by = b.getY(), py=p1.getY(), px = p1.getX(), p2x = p2.getX(),p2y = p2.getY();

	if (bx <= p1.getWidth()){
		if (by>=py && by <= py + p1.getHeight()){
			dirx*=-1;
		}else{
			allegro_message("Left Paddle Lost :( Right Paddle Won :)\n");
			//al_show_native_message_box(NULL,"Result","Result:","Left Paddle Lost :( Right Paddle Won :)\n",NULL,ALLEGRO_MESSAGEBOX_ERROR);
			resetBall(b,p1,1);
			return;
		}
	}else if (bx>= scrx-p2.getWidth()){
		if (by>=p2y && by <= p2y + p2.getHeight()){
			dirx*=-1;
		}else{
			allegro_message("Left Paddle Lost :( Right Paddle Won :)\n");
			//al_show_native_message_box(NULL,"Result","Result:","Left Paddle Lost :( Right Paddle Won :)\n",NULL,ALLEGRO_MESSAGEBOX_ERROR);
			resetBall(b,p2,2);
			return;
		}
	}else if ((diry<0 && by<=0) || (diry>0 &&  by>= ( scry-b.getHeight() ))){
		//	allegro_message("lol\n");cout<<diry << " " << by;
			diry*=-1;
	}

	b.setX(b.getX()+movespeed*dirx);
	b.setDirX(dirx);b.setDirY(diry);
	b.setY(b.getY()+movespeed*diry);
	b.setDirX(dirx);b.setDirY(diry);
}


int main(){
	if(allegro_init()){
		allegro_message("Allegro Failed to Initialize\n");
	}

	set_window_title("Pong");

	if (install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL)){
		allegro_message("Sound Error\n");
	}

	if(install_keyboard()){
		allegro_message("Cannot initialize keyboard\n");
	}


	install_timer();
	int buttons= install_mouse();
	set_color_depth(32);

	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,scrx,scry,0,0)){
		allegro_message("Video Error\n");
	}
	LOCK_VARIABLE(aftResult);

	LOCK_FUNCTION(CloseButtonCallBack);
	LOCK_VARIABLE(closeWindow);

	LOCK_FUNCTION(Increment);
	LOCK_VARIABLE(counter);

	install_int_ex(Increment,BPS_TO_TIMER(80));
	set_close_button_callback(CloseButtonCallBack);

	BITMAP *Buffer= create_bitmap(scrx,scry);

	//StartScreen(screen);

	Paddle p1;
	Paddle p2;
	Ball b1;
	resetBall(b1);
	b1.setHeight(15);b1.setWidth(15);
	p1.setX(0);	p1.setY(scry/2); p1.setSize(4,80);
	p2.setX(scrx-p1.getWidth()-1); p2.setY(scry/2);p2.setSize(4,80);

	int movSpeed = 3;
	int oticks =0;
	while(!closeWindow ){
		if (key[KEY_ESC]) closeWindow = true;

		//Update w/ timer
		while(ticks>0){
			if (aftResult == 1){
				if(key[KEY_SPACE]) aftResult = 0;
				ticks = 0;
				continue;
			}

			oticks = ticks;
			//clear_keybuf();
			int locy = scry-p1.getHeight(),locy2= scry-p2.getHeight();
			int cury =p1.getY(), cury2 = p2.getY();

			if (key[KEY_W])
				if(p1.getY() >= 0 && cury<=locy )
					p1.setY(p1.getY()-movSpeed);
				else
					p1.setY((p1.getY()<0)?0:locy);
			else if(key[KEY_S])
				if(p1.getY() >= 0 && cury<= locy)
					p1.setY(p1.getY()+movSpeed);
				else
					p1.setY((p1.getY()<0)?0:locy);
			if (key[KEY_UP])
				if(p2.getY() >= 0 && cury2<= locy2)
					p2.setY(p2.getY()-movSpeed);
				else
					p2.setY((p2.getY()<0)?0:locy2);
			else if(key[KEY_DOWN])
				if(p2.getY() >= 0 && cury2 <= locy2)
					p2.setY(p2.getY()+movSpeed);
				else
					p2.setY((p2.getY()<0)?0:locy2);

			moveBall(b1,p1,p2);


			ticks--;
			if (oticks<=ticks )break;
		}
		//Draw

		show_mouse(Buffer);
		DrawLine(Buffer);
		DrawPaddle(p1,Buffer);
		DrawPaddle(p2,Buffer);
		DrawBall(b1,Buffer);

		textprintf_ex(Buffer, font,0,scry-10,makecol(255,255,255),-1,"Player 1:%d", score1);
		textprintf_right_ex(Buffer, font,scrx,scry-10,makecol(225,225,225),-1,"Player 2: %d", score2);
		blit (Buffer, screen,0,0,0,0,scrx,scry);
		rest(20);
		clear_bitmap(Buffer);
	}
	destroy_bitmap(Buffer);
	allegro_exit();
	return 0;
}
END_OF_MAIN()
