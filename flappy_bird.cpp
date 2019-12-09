#include <graphics.h>
#include <conio.h>
#define HEIGHT 600
#define WIDTH 350

#pragma comment(lib, "Winmm.lib")

IMAGE img_bk, img_bd1, img_bd2, 
img_bar_up1, img_bar_up2, img_bar_down1, img_bar_down2; 
int bird_x, bird_y;
int bar_x, bar_up, bar_down, bar_width;
int score;
static int i;
char score1[100];
int gameover;
int t;
void startup(void);
void show(void);
void without_input(void);
void with_input(void);
int freefall(int, int);
void itos(char *dst, int src);
int main(void) {
	startup();
	while (!gameover) {
		show();
		without_input();
		with_input();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}

void startup(void) {
	t = 0;
	gameover = 0;
	score = 0;
	initgraph(WIDTH, HEIGHT, NULL);
	loadimage(&img_bk, "D:\\flappy bird\\background.jpg");
	loadimage(&img_bd1, "D:\\flappy bird\\bird1.jpg");
	loadimage(&img_bd2, "D:\\flappy bird\\bird2.jpg");
	loadimage(&img_bar_up1, "D:\\flappy bird\\bar_up1.gif");
	loadimage(&img_bar_up2, "D:\\flappy bird\\bar_up2.gif");
	loadimage(&img_bar_down1, "D:\\flappy bird\\bar_down1.gif");
	loadimage(&img_bar_down2, "D:\\flappy bird\\bar_down2.gif");
	bird_x = WIDTH / 6;
	bird_y = HEIGHT / 2;
	bar_x = WIDTH / 3 * 2;
	bar_up = rand() % 300 - 600;
	bar_width = 100;
	bar_down = bar_up + bar_width + 600;
	BeginBatchDraw();

	mciSendString(
		"open D:\\flappy bird\\background.mp3 type MPEGVideo alias bkmusic", 
		NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
}
void show(void) {
	setlinecolor(GREEN);
	line(0, 0, WIDTH, HEIGHT);
	putimage(0, 0, &img_bk, SRCCOPY);
	putimage(bar_x, bar_up, &img_bar_up1, NOTSRCERASE);
	putimage(bar_x, bar_up, &img_bar_up2, SRCINVERT);
	putimage(bar_x, bar_down, &img_bar_down1, NOTSRCERASE);
	putimage(bar_x, bar_down, &img_bar_down2, SRCINVERT);
	putimage(bird_x, bird_y, &img_bd1, NOTSRCERASE);
	putimage(bird_x, bird_y, &img_bd2, SRCINVERT);
	outtextxy(WIDTH * 9 / 10, HEIGHT * 9 / 10, score1);
	FlushBatchDraw();
	Sleep(50);
}

void without_input(void) {
   	t++;
  	bird_y = freefall(bird_y, t / 5);
	if (bird_y > HEIGHT);
    	bar_x -= 3;
	if (bar_x + 140 < 0) {
		bar_x = WIDTH;
		score += 123;      
 		itos(score1, score);
		bar_up = rand() % 300 - 600;
		bar_width = 100;
		bar_down = bar_up + bar_width + 600;
	}
	if ((bird_x <= bar_x + 140 && bird_x + 34 >= bar_x)
		&& !(bird_y <= bar_down && bird_y >= bar_up + 600))
	{
		gameover = 1;
	}
	else if (bird_y >= HEIGHT || bird_y <= 0) gameover = 1;
}
void with_input(void) {
	int c;
	if (_kbhit()) {
		c = _getch();
		if (c == ' ') {
			bird_y -= 5;
			t = 0;
		}
	}
}

int freefall(int y, int time) {
	return time * time / 2 + y;
}

void itos(char *dst, int src) {//hhhh I didn't know the sprintf function
	i = 0; 
	if (src > 10) {		
		itos(dst + i, src / 10);
		i++;
	}
	*(dst + i) = src % 10 + '0';
}
