#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define WIDTH 41
#define HEIGHT 20

void gotoxy(int, int);
void show(void);
void startup(void);
void without_input(void);
void with_input(void);
/*
canvas:
0 space
1 ball
2 brick
3 bar
-1 vertical wall
-2 horizontal wall
*/
int canvas[HEIGHT][WIDTH] = { 0 };
int i, j;
int ball_x, ball_y, ball_vx, ball_vy;
int bar_right, bar_left, bar_len;
int HIT;

int main(void) {
	startup();
	while (!HIT) {
		show();
		without_input();
		with_input();
	}
	printf("you lose!!!!!\nHHHHH\n");
	system("pause");
}
void with_input(void) {
	static int c;
	if (_kbhit()) {
		c = _getch();
		switch (c){
		case 'a': {
			if (bar_left > 0) {
				canvas[HEIGHT - 2][bar_right] = 0;
				canvas[HEIGHT - 2][bar_left - 1] = 3;
				bar_right--;
				bar_left--;
			}
			break;
		}
		case 'd': {
			if (bar_right < WIDTH - 2) {
				canvas[HEIGHT - 2][bar_left] = 0;
				canvas[HEIGHT - 2][bar_right + 1] = 3;
				bar_right++;
				bar_left++;
			}
			break;
		}
		};
	}
}
void without_input(void) {
	static int new_ball_x, new_ball_y;
	static int ping;
	if (ping == 1) {
		new_ball_x = ball_x + ball_vx;
		if ((new_ball_y = ball_y + ball_vy) == 0) ball_vy = 1;
		switch (canvas[new_ball_y][new_ball_x]) {
		case 0: {//nothing
			canvas[ball_y][ball_x] = 0;
			canvas[new_ball_y][new_ball_x] = 1;
			ball_y = new_ball_y;
			ball_x = new_ball_x;
			break;
		}
		case 2: {//brick
			canvas[new_ball_y][new_ball_x] = 0;
			ball_vy *= -1;
			break;
		}
		case 3: {//bar
			ball_vy *= -1;
			break;
		}
		case -1: {
			ball_vx *= -1;
			break;
		}
		case -2: {
			HIT = 1;
		}
		}
		ping = 0;
	}
	ping++;
}
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void startup(void) {
	HIT = 0;
	ball_vx = -1;
	ball_vy = -1;
	bar_len = WIDTH / 4;
	bar_right = WIDTH / 2 + bar_len / 2;
	bar_left = WIDTH / 2 - bar_len / 2;
	for (i = bar_left; i <= bar_right; i++) {
		canvas[HEIGHT - 2][i] = 3;
	}
	ball_x = rand() % WIDTH;
	ball_y = rand() % (HEIGHT - 4) + 3;
	canvas[ball_y][ball_x] = 1;
	for (j = 0; j < WIDTH; j++) {
		canvas[1][j] = canvas[2][j] = canvas[0][j] = 2;
		canvas[HEIGHT - 1][j] = -2;
	}
	for (i = 0; i < HEIGHT; i++) {
		canvas[i][WIDTH - 1] = -1;
	}
}
void show(void) {
	gotoxy(0, 0);
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (!canvas[i][j]) printf(" ");
			else if (canvas[i][j] == 1) printf("O");
			else if (canvas[i][j] == 2) printf("#");
			else if (canvas[i][j] == 3) printf("*");
			else if (canvas[i][j] == -1) printf("|");
			else if (canvas[i][j] == -2) printf("_");
		}
		printf("\n");
	}
}
