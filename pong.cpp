#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <cstdio>

#define UP 38
#define DOWN 40
#define LEFT 37
#define RIGHT 39


void gotoxy(int x, int y);
void hideCursor(void);
void drawBorders(void);
void drawLine(int mn, int mx);

class Paddle{
private:
	int x, y;
	void impact(void);
	void treeInLine(int character);
public:
	Paddle(int _x, int _y); 
	int X(void){return x;}
	int Y(void){return y;}
    void rivalmove(int ballY);
    void clean(void);
    void drawPaddle(void);
    void move(void); 
    bool giveup = true;
    int mode = 0;
};

Paddle::Paddle(int _x, int _y){
	x = _x;
	y = _y;
}
void Paddle::impact(void){
	if(y+1>=22){
		y -= 1;
	}
	if(y-1<=2){
		y+= 1;
	}
	return;
}
void Paddle::treeInLine(int character){
	int i = -1;
	for(i;i<= 1;i++){
		gotoxy(x,y+i);printf("%c", character);
	}
	return;
}
void Paddle::drawPaddle(void){
	Paddle::treeInLine(219);
	return;
}
void Paddle::clean(void){
	Paddle::treeInLine(32);
	return;
}
void Paddle::rivalmove(int ballY){
	Paddle::clean();
	if(mode == 1){
		int m  = rand() % 2;
	    if(m == 1){
		    y++;
	    }
	    else{
		    y--;
	    }
	    
	
	}
	else if(mode == 2){
		if(ballY>=y+1){
			y++;
		}
		if(ballY<=y-1){
			y--;
		}
	}
	else if(mode == 3){
		if(kbhit()){
			char key = getch();
			switch(key){
				case 'i':y-=1;break;
				case 'k':y+=1;break;
			}
		}
	}
	Paddle::impact();
	Paddle::drawPaddle();
	return;
	
}
void Paddle::move(void){

	Paddle::clean();
	if(kbhit()){
		char key = getch();
		switch(key){
			case 'w':y-=1;break;
			case 's':y+=1;break;
			case 'q':giveup = true;break;
		}
	}
	Paddle::impact();
	Paddle::drawPaddle();
	return;
}
void startGame(int m);
class Ball{
private:
	int x, y;
	int moveX =1, moveY=1;
	void reload(void);
	void changeDirection(void);
	int y1, y2;
public:
	Ball(int _x, int _y);
	int X(void){return x;}
	int Y(void){return y;}
	void move(void);
	void collition(void);
	void getPaddleCoords(int py1, int py2);

};
Ball::Ball(int _x, int _y){
	x = _x;
	y = _y;
	Ball::reload();
}
void Ball::reload(void){
	gotoxy(x,y);printf(" ");
	x = rand()%41+39;
	y = rand()%20+3;
	int dmx = rand()%2, dmy = rand()%2;
	if(dmx==0){
		moveX *= -1;
	}
	if(dmy==0){
		moveY *= -1;
	}
	gotoxy(x,y);printf("*");  
	return;
}
void Ball::changeDirection(void){
	moveX *= -1;
	moveY *= -1;
	return;
}
void Ball::move(void){
	gotoxy(x,y);printf(" ");
	x += moveX;
	y += moveY;
	Ball::collition();
	gotoxy(x,y);printf("*");
	return;
}
void Ball::collition(void){
	if(y>=21 || y<=3){
		moveY *=-1;
	}
	if((y>=y1-1 && y<=y1+1) && x==4){
		changeDirection();
	}
	if((y>=y2-1 && y<=y2+1) && x == 75){
		changeDirection();
	}
	if(x==3 || x==75){
		Ball::reload();
	}
	return;
}

void Ball::getPaddleCoords(int py1, int py2){
	y1 = py1;
	y2 = py2;
	return;
}

int main(){
	system("cls");
	drawBorders();
	gotoxy(36,5);printf("P O N G");
	gotoxy(14,10);printf("ONE PLAYER");//10
	gotoxy(36,10);printf("MULTIPLAYER");//12
	gotoxy(59,10);printf("EXTREME");//7
	gotoxy(15,15);printf("[s] = done");
	gotoxy(15,16);printf("[a] = <-");
	gotoxy(15,17);printf("[d] = ->");
	char key = 0;
	int index = 0, m=1;
	int change = index;
	bool done = true;
	drawLine(14,22); 
	do{
		if(kbhit()){
			key = getch();
			switch(key){
				case LEFT:index-=1;break;
				case RIGHT:index+=1;break;
				case 'a':index-=1;break;
				case 'd':index+= 1;break;
				case 's':done = false;break;
			}
		}
		if(change != index){
			switch(index){
				
			    case 0:drawLine(14,22);break;
			    case 1:drawLine(36,45);break;
			    case 2:drawLine(59, 64);break;
			    case 3:index = 0;drawLine(14,22);break;
			    case -1:index =2;drawLine(59, 64);break;
			}
			change = index;
		}
		

		
	}while(done);
	if(index == 0){
		startGame(m);
	}
	else if(index == 1){
		m = 3;
		startGame(m);
	}
	else{
		startGame(2);
	}
	return 0;
}
void drawLine(int mn, int mx){
	int x = 12;
	for(x;x<=68;x++){
		gotoxy(x,11);printf(" ");
	}
	for(mn;mn<=mx+1;mn++){
		gotoxy(mn, 11);printf("%c",196);
	}
}
void startGame(int m){
	system("cls");
	hideCursor();
	drawBorders();
	Paddle player_paddle (4, 10);
	Paddle rival(75,10);
	rival.mode = m;
	Ball pelota(1,1);
	int ppoints = 0; //ppoints == player points;
	int cpoints = 0; // cpoints == computer points
	while(ppoints < 5 || cpoints < 5 || !player_paddle.giveup){
		pelota.getPaddleCoords(player_paddle.Y(),rival.Y());
		pelota.move();
		player_paddle.move();
		rival.rivalmove(pelota.Y());
		Sleep(100);
	}
	return;
}

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
	return;
}
void hideCursor(void){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 0;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
	return;
}
void drawBorders(void){
	int x =2;
	int y =2;
	for(x;x<=76;x++){
		gotoxy(x,y);printf("%c",205);
		y = 22;
		gotoxy(x,y);printf("%c", 205);
		y = 2;
	}
	x = 2;
	for(y;y<=22;y++){
		gotoxy(x,y);printf("%c", 186);
		x = 77; 
		gotoxy(x,y);printf("%c", 186);
		x = 2;
	}
	gotoxy(2,2);printf("%c", 201);
	gotoxy(77,2);printf("%c", 187);
	gotoxy(2,22);printf("%c", 200);
	gotoxy(77,22);printf("%c", 188);
	return;
}