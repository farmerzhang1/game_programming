//故意取这个名字的（词汇量啊hhhh） 好像还有bug（懒惰）
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define WIDTH 30
#define HEIGHT 20

void gotoxy(int, int);
void show(void);
void startup(void);
void without_input(void);
void with_input(void);
void move_dir(int c);

int i, j;
int HIT;
static int c;
int food_x, food_y;
int canvas[HEIGHT][WIDTH] = { 0 };
/*
canvas:
0		space			
1		serpente head	@
>1		serpente body	*
-1		frame			#
-2		food			F

*//*
int main(void) {
	startup();
	while (!HIT) {
		show();
		without_input();
		with_input();
	}
	show();
	printf("you lose\nHHHHHHH\n\n");
	system("pause");
}

void show(void) {
	gotoxy(0, 0);
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (!canvas[i][j]) printf(" ");
			else if (canvas[i][j] == 1) printf("@");
			else if (canvas[i][j] > 1) printf("*");
			else if (canvas[i][j] == -1) printf("#");
			else if (canvas[i][j] == -2) printf("F");
		}
		printf("\n");
	}
}

void startup(void) {
	c = 'w';
	HIT = 0;
	for (i = 0; i < WIDTH; i++) {
		canvas[0][i] = -1;
		canvas[HEIGHT - 1][i] = -1;
	}
	for (j = 0; j < HEIGHT; j++) {
		canvas[j][0] = -1;
		canvas[j][WIDTH - 1] = -1;
	}
	canvas[HEIGHT / 2][WIDTH / 2] = 1;//head
	for (i = 1; i <= 5; i++) {//body
		canvas[HEIGHT / 2][WIDTH / 2 - i] = i + 1;
	}
	food_x = rand() % (WIDTH - 5);
	food_y = rand() % (HEIGHT - 5);
	canvas[food_y][food_x] = -2;
}
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void without_input(void) {
	move_dir(c);
	Sleep(200);
}
void with_input(void) {
	if (_kbhit()) {
		c = _getch();
		move_dir(c);
	}

}

void move_dir(int c) {
	static int max = 0;
	static int head_x, head_y;
	static int tail_x, tail_y;
	for (i = 1; i < HEIGHT - 1; i++) {
		for (j = 1; j < WIDTH - 1; j++) {
			if (canvas[i][j] > 0) canvas[i][j]++;
			if (max < canvas[i][j]) {
				max = canvas[i][j];
				tail_x = j;
				tail_y = i;
			}
			if (canvas[i][j] == 2) {
				head_x = j;
				head_y = i;
			}
		}
	}
	switch (c) {
	case 'a': {
		if (canvas[head_y][head_x - 1] == -2) {//food, len++
			canvas[head_y][head_x - 1] = 1;
			food_x = rand() % (WIDTH - 5);
			food_y = rand() % (HEIGHT - 5);
			canvas[food_y][food_x] = -2;
		}
		else if (canvas[head_y][head_x - 1] == 0) {
			canvas[head_y][head_x - 1] = 1;
			canvas[tail_y][tail_x] = 0;
		}
		else if (canvas[head_y][head_x - 1] == -1 || canvas[head_y][head_x - 1] > 1) {
			HIT = 1;
		}
		break;
	}
	case 's': {
		if (canvas[head_y + 1][head_x] == -2) {//food, len++
			canvas[head_y + 1][head_x] = 1;
			food_x = rand() % (WIDTH - 5);
			food_y = rand() % (HEIGHT - 5);
			canvas[food_y][food_x] = -2;
		}
		else if (canvas[head_y + 1][head_x] == 0) {
			canvas[head_y + 1][head_x] = 1;
			canvas[tail_y][tail_x] = 0;
		}
		else if (canvas[head_y + 1][head_x] == -1 || canvas[head_y + 1][head_x] > 1) {
			HIT = 1;
		}
		break;
	}
	case 'w': {
		if (canvas[head_y - 1][head_x] == -2) {//food, len++
			canvas[head_y - 1][head_x] = 1;
			food_x = rand() % (WIDTH - 5);
			food_y = rand() % (HEIGHT - 5);
			canvas[food_y][food_x] = -2;
		}
		else if (canvas[head_y - 1][head_x] == 0) {
			canvas[head_y - 1][head_x] = 1;
			canvas[tail_y][tail_x] = 0;
		}
		else if (canvas[head_y - 1][head_x] == -1 || canvas[head_y - 1][head_x] > 1) {
			HIT = 1;
		}
		break;
	}
	case 'd': {
		if (canvas[head_y][head_x + 1] == -2) {//food, len++
			canvas[head_y][head_x + 1] = 1;
			food_x = rand() % (WIDTH - 5);
			food_y = rand() % (HEIGHT - 5);
			canvas[food_y][food_x] = -2;
		}
		else if (canvas[head_y][head_x + 1] == 0) {
			canvas[head_y][head_x + 1] = 1;
			canvas[tail_y][tail_x] = 0;
		}
		else if (canvas[head_y][head_x + 1] == -1 || canvas[head_y][head_x + 1] > 1) {
			//hit wall or itself
			HIT = 1;
		}
		break;
	}
	}
}
