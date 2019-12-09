#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

#define HEIGHT 800
#define WIDTH 590
#define NBULLET 5
#define NALIEN 5

IMAGE background;
IMAGE plane_not_ex1, plane_not_ex2;
IMAGE plane_ex1, plane_ex2;
IMAGE bullet1, bullet2;
IMAGE alien1, alien2;
int plane_x, plane_y;
int bullet_x[NBULLET], bullet_y[NBULLET];
int alien_x[NALIEN], alien_y[NALIEN];
int explode;
int score;

void startup(void);
void show(void);
void with_input(void);
void without_input(void);

int main()
{
	startup(); 
	while (!explode)
	{
		show();
		without_input();
		with_input();
	}
	show();
	_getch();
	closegraph();
	return 0;
}

void startup(void) {
	int i;
	for (i = 0; i < NBULLET; i++) {
		bullet_x[i] = rand() % (WIDTH - bullet1.getwidth());
		bullet_y[i] = -bullet1.getheight() - 1000;
	}
	for (i = 0; i < NALIEN; i++) {
		alien_x[i] = rand() % WIDTH;
		alien_y[i] = 0;
	}
	plane_x = WIDTH / 2;
	plane_y = HEIGHT - 110;
	explode = 0;
	score = 0;
	initgraph(WIDTH, HEIGHT);
	loadimage(&background, "D:\\hit_plane\\background.jpg");
	loadimage(&plane_not_ex1, "D:\\hit_plane\\planeNormal_1.jpg");
	loadimage(&plane_not_ex2, "D:\\hit_plane\\planeNormal_2.jpg");
	loadimage(&bullet1, "D:\\hit_plane\\bullet1.jpg");
	loadimage(&bullet2, "D:\\hit_plane\\bullet2.jpg");
	loadimage(&alien1, "D:\\hit_plane\\enemyPlane1.jpg");
	loadimage(&alien2, "D:\\hit_plane\\enemyPlane2.jpg");
	loadimage(&plane_ex1, "D:\\hit_plane\\planeExplode_1.jpg");
	loadimage(&plane_ex2, "D:\\hit_plane\\planeExplode_2.jpg");
	BeginBatchDraw();
}

void show(void) {
	int i;
	putimage(0, 0, &background);
	if (!explode) {
		putimage(plane_x, plane_y, &plane_not_ex1, NOTSRCERASE);
		putimage(plane_x, plane_y, &plane_not_ex2, SRCINVERT);
	}
	else {
		putimage(plane_x, plane_y, &plane_ex1, NOTSRCERASE);
		putimage(plane_x, plane_y, &plane_ex2, SRCINVERT);
	}
	for (i = 0; i < NBULLET; i++) {
		putimage(bullet_x[i], bullet_y[i], &bullet1, NOTSRCERASE);
		putimage(bullet_x[i], bullet_y[i], &bullet2, SRCINVERT);
	}
	for (i = 0; i < NALIEN; i++) {
		putimage(alien_x[i], alien_y[i], &alien1, NOTSRCERASE);
		putimage(alien_x[i], alien_y[i], &alien2, SRCINVERT);
	}
	char scorestr[5];
	sprintf(scorestr, "%d", score);
	outtextxy(WIDTH - 50, HEIGHT - 50, scorestr);
	FlushBatchDraw();
}
void with_input(void) { 
	MOUSEMSG mouse;
	if (MouseHit()) {
		mouse = GetMouseMsg();
		if (mouse.uMsg == WM_MOUSEMOVE) {
			plane_x = mouse.x - plane_not_ex1.getwidth() / 2;
			plane_y = mouse.y - plane_not_ex1.getheight() / 2;
		}
		else if (mouse.uMsg == WM_LBUTTONDOWN) {
			for (int i = 0; i < NBULLET; i++) {
				if (bullet_y[i] <= -bullet1.getheight()) {
					bullet_x[i] = plane_x + plane_not_ex1.getwidth() / 2 ;
					bullet_y[i] = plane_y - 85;
					break;
				}
			}
		}
	}

}
void without_input(void) { 
	int i;
	for (i = 0; i < NALIEN; i++) {
		if (alien_y[i] < HEIGHT) alien_y[i]++;
		else
		{
			alien_y[i] = -alien1.getheight();
			alien_x[i] = rand() % (WIDTH - alien1.getwidth());
		}
		if ((alien_y[i] + alien1.getheight() >= plane_y && alien_y[i] <= plane_y + plane_not_ex1.getheight())
			&& (alien_x[i] + alien1.getwidth() >= plane_x && alien_x[i] <= plane_x + plane_not_ex1.getwidth()))
		{
			explode = 1;
		}
	}
	for (i = 0; i < NBULLET; i++) {
		if (bullet_y[i] > -bullet1.getheight()) bullet_y[i]--;
		for (int j = 0; j < NALIEN; j++) {//if boom
			if ((bullet_y[i] <= alien_y[j] + alien1.getheight())
				&& (bullet_x[i] + bullet1.getwidth() >= alien_x[j] && bullet_x[i] <= alien_x[j] + alien1.getwidth())) {
				alien_x[j] = rand() % (WIDTH - alien1.getwidth()); 
				alien_y[j] = -alien1.getheight();
				bullet_y[i] = -bullet1.getheight() - 1000;
				score++;
			}
		}
	}
}
