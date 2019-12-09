#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#define HEIGHT 480
#define WIDTH 640

int ball_x, ball_y;
int ball_vx, ball_vy;
int radius;
int bar1_left, bar1_right, bar1_top, bar1_bottom;
int bar2_left, bar2_right, bar2_top, bar2_bottom;
int bar_height, bar_width;
int score1, score2;
char scorestr[20];
void startup(void);
void clean(void);
void without_input(void);
void with_input(void);
void show(void);

int main()
{
	startup();
	while (1)
	{
		clean();
		without_input();
		with_input();
		show();
	}
	return 0;
}

void startup(void) {
	score1 = 0;
	score2 = 0;
	ball_x = WIDTH / 2;
	ball_y = HEIGHT / 2;
	radius = 20;
	ball_vx = 1;
	ball_vy = 1;
	bar_width = WIDTH / 30;
	bar_height = HEIGHT / 2;
	bar1_left = 0;
	bar1_top = HEIGHT / 4;
	bar1_right = bar1_left + bar_width;
	bar1_bottom = bar1_top + bar_height;

	bar2_left = WIDTH - bar_width;
	bar2_top = HEIGHT / 4;
	bar2_right = bar2_left + bar_width;
	bar2_bottom = bar2_top + bar_height;

	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
}
void clean(void) { 
	setfillcolor(BLACK);
	setcolor(BLACK);
	fillcircle(ball_x, ball_y, radius);
	setfillcolor(BLACK);
	bar(bar1_left, bar1_top, bar1_right, bar1_bottom);
	bar(bar2_left, bar2_top, bar2_right, bar2_bottom);
}
void without_input(void) {
	ball_y += ball_vy;
	if (ball_y + radius == HEIGHT || ball_y - radius == 0) ball_vy *= -1;
	ball_x += ball_vx;
	if ((ball_x + radius == bar2_left && ball_y + radius <= bar2_bottom && ball_y - radius >= bar2_top)
		|| (ball_x - radius == bar1_right && ball_y + radius <= bar1_bottom && ball_y - radius >= bar1_top))
	{
		ball_vx *= -1;
	}
	else if (ball_x + radius == WIDTH 
		&& !(ball_y + radius <= bar2_bottom && ball_y - radius >= bar2_top))
	{
		ball_vx *= -1;
		score2++;
	}
	else if (ball_x - radius == 0
		&& !(ball_y + radius <= bar1_bottom && ball_y - radius >= bar1_top))
	{
		ball_vx *= -1;
		score1++;
	}
	sprintf(scorestr, "%d VS %d", score1, score2);
}
void with_input(void) {
	int step = 1;
	if (GetAsyncKeyState(0x57) & 0x8000)
		if (bar1_top >= 0) bar1_top -= step;
	if ((GetAsyncKeyState(0x53) & 0x8000))
		if (bar1_top + bar_height <= HEIGHT) bar1_top += step;
	if ((GetAsyncKeyState(VK_UP) & 0x8000))
		if (bar2_top >= 0) bar2_top -= step;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000))
		if (bar2_top + bar_height <= HEIGHT) bar2_top += step;

	bar1_bottom = bar1_top + bar_height;
	bar2_bottom = bar2_top + bar_height;
}
void show(void) {
	setfillcolor(RED);
	setcolor(BLACK);
	fillcircle(ball_x, ball_y, radius);
	setfillcolor(RGB(242, 56, 230));
	bar(bar1_left, bar1_top, bar1_right, bar1_bottom);
	bar(bar2_left, bar2_top, bar2_right, bar2_bottom);
	settextcolor(GREEN);
	outtextxy(WIDTH / 2, HEIGHT - 50, scorestr);
	FlushBatchDraw();
}
