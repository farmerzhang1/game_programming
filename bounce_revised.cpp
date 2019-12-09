#include <conio.h>
#include <graphics.h>
#define HEIGHT 500
#define WIDTH 800
#define BRICKNUM 20
/*found  that this is cpp, so maybe the struct syntax is not usable here...
found so long for bugs
and it returns some info about class not struct...
*/
void startup(void);
void clean(void);
void with_input(void);
void without_input(void);
void show(void);

int ball_x, ball_y;
int ball_vx, ball_vy;
int radius;
int bar_x, bar_y;
int bar_height, bar_width;
int bar_left, bar_right, bar_top, bar_bottom;
int brick_state[BRICKNUM];
int brick_height, brick_width;
int i, j;
int gameover;
int main(void)
{
	startup();
	while (1)
	{
		clean();
		without_input();
		with_input();
		show();
	}
	if (gameover == -1) outtext("you lose!!!");
	else if (gameover == 1) outtext("you win!!!");
	return 0;
}
void startup(void) 
{
	initgraph(WIDTH, HEIGHT, NULL);
	gameover = 0;
	ball_x = WIDTH / 2;
	ball_y = HEIGHT / 2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;
	bar_height = HEIGHT / 20;
	bar_width = WIDTH / 2;
	bar_x = WIDTH / 2;
	bar_y = HEIGHT - bar_height / 2;
	bar_left = bar_x - bar_width / 2;
	bar_right = bar_x + bar_width / 2;
	bar_top = bar_y - bar_height / 2;
	bar_bottom = bar_y + bar_height / 2;

	brick_width = WIDTH / BRICKNUM;
	brick_height = HEIGHT / BRICKNUM;
	for (i = 0; i < BRICKNUM; i++) {
		brick_state[i] = 1;
	}
	BeginBatchDraw();
}


void clean(void) {
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y, radius);
	fillrectangle(bar_left, bar_top, bar_right, bar_bottom);
	for (i = 0; i < BRICKNUM; i++) {
		fillrectangle(brick_width * i, 0, brick_width * (i + 1), brick_height);		
	}
}
void with_input(void) {
	MOUSEMSG mouse;
	if (MouseHit()) {
		mouse = GetMouseMsg();
		bar_x = mouse.x;
		if (bar_x - bar_width / 2 < 0) {
			bar_left = 0;
			bar_right = bar_width;
		}
		else if (bar_x + bar_width / 2 > WIDTH) {
			bar_right = WIDTH; 
			bar_left = bar_right - bar_width;
		}
		else
		{
			bar_left = bar_x - bar_width / 2;
			bar_right = bar_x + bar_width / 2;
		}
	}
}
void without_input(void) {
	int all0 = 1;
	ball_x += ball_vx;
	ball_y += ball_vy;
	if (ball_x <= radius || ball_x >= WIDTH - radius) ball_vx *= -1;
	if ((ball_y + radius == bar_top && ball_x <= bar_right && ball_x >= bar_left)|| ball_y - radius == 0) ball_vy *= -1;
	else if (ball_y - radius == brick_height && brick_state[ball_x / brick_width]) {
		brick_state[ball_x / brick_width] = 0;		
		ball_vy *= -1;
	}
	else if (ball_y + radius == HEIGHT) {
		ball_vy *= -1;
		gameover = -1;
	}
}
void show(void) {
	setcolor(BLACK);
	setfillcolor(RED);
	fillcircle(ball_x, ball_y, radius);
	setfillcolor(GREEN);
	fillrectangle(bar_left, bar_top, bar_right, bar_bottom);
	setfillcolor(RGB(255, 192, 203));
	for (i = 0; i < BRICKNUM; i++) {
		if (brick_state[i]) {
			fillrectangle(brick_width * i, 0, brick_width * (i + 1), brick_height);
		}
	}
	FlushBatchDraw();
}
