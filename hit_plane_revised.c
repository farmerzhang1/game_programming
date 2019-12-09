//fuck, forgot to add () to the end of kbhit... find so long for the bug
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define WIDTH 30
#define HEIGHT 20
#define ALIENNUM 5

void gotoxy(int, int);
void show(void);
void startup(void);
void without_input(void);
void with_input(void);

int i, j;
//0 stands for space, 1 for plane, 2 for bullets, 3 for sprites
int canvas[HEIGHT][WIDTH] = { 0 };
int plane_x, plane_y;
int alien_x[ALIENNUM], alien_y[ALIENNUM];
int score;


int main(void) {
	startup();
	while (1) {
		show();
		without_input();
		with_input();
	}
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
	for (i = 0; i < ALIENNUM; i++) {
		alien_x[i] = rand() % WIDTH;
		alien_y[i] = rand() % 3;
		canvas[alien_y[i]][alien_x[i]] = 3;
	}
	plane_x = WIDTH / 2;
	plane_y = HEIGHT - 1;
	canvas[plane_y][plane_x] = 1;	
	score = 10;
}

void show(void) {
	gotoxy(0, 0);
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (!canvas[i][j]) printf(" ");
			else if (canvas[i][j] == 1) printf("*");
			else if (canvas[i][j] == 2) printf("|");
			else if (canvas[i][j] == 3) printf("@");
		}
		printf("\n");
	}
	printf("your score is %d", score);
}
void without_input(void) {
	static int k = 0, ping = 0;
	
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (canvas[i][j] == 2) 
			{
				canvas[i][j] = 0;
				if (i > 0) canvas[i - 1][j] = 2;//bullet up				
				for (k = 0; k < ALIENNUM; k++) {
					if (alien_x[k] == j && alien_y[k] == i) {
						alien_x[k] = rand() % WIDTH;
						alien_y[k] = rand() % 3;
						canvas[alien_y[k]][alien_x[k]] = 3;
						canvas[i - 1][j] = 0;
						score++;
					}
				}
			}
			
		}
	}
	if (ping == (100 - score) / 5) {
		for (k = 0; k < ALIENNUM; k++) 
		{
			if (alien_y[k] < HEIGHT - 1) {
				canvas[alien_y[k]++][alien_x[k]] = 0;
				canvas[alien_y[k]][alien_x[k]] = 3;
			}
			else
			{
				canvas[alien_y[k]][alien_x[k]] = 0;
				alien_y[k] = rand() % 3;
				alien_x[k] = rand() % WIDTH;
				canvas[alien_y[k]][alien_x[k]] = 3;
				score -= 5;
			}
		}
		ping = 0;
	}
	ping++;

}

void with_input(void) {
	int c;
	if (_kbhit()) {
		c = _getch();
		switch (c) {
		case 'a': {
			if (plane_x > 0) {
				canvas[plane_y][plane_x--] = 0;
				canvas[plane_y][plane_x] = 1;
			}
			break; 
		}
		case 'A': {
			if (plane_x > 0) {
				canvas[plane_y][plane_x--] = 0;
				canvas[plane_y][plane_x] = 1;
			}
			break;
		}
		case 's': {
			if (plane_y < HEIGHT - 1) {
				canvas[plane_y++][plane_x] = 0;
				canvas[plane_y][plane_x] = 1;
			}
			break;
		}
		case 'S': {
			if (plane_y < HEIGHT - 1) {
				canvas[plane_y++][plane_x] = 0;
				canvas[plane_y][plane_x] = 1;
			}
			break;
		}
		case 'd': {
			if (plane_x < WIDTH - 1) {
				canvas[plane_y][plane_x++] = 0;
				canvas[plane_y][plane_x] = 1;
			}
			break;
		}
		case 'D': {
			if (plane_x < WIDTH - 1) {
				canvas[plane_y][plane_x++] = 0;
				canvas[plane_y][plane_x] = 1;
			}
			break;
		}
		case 'w': {
			if (plane_y > 0) {
				canvas[plane_y--][plane_x] = 0;
				canvas[plane_y][plane_x] = 1;
			}
			break;
		}
		case 'W': {
			if (plane_y > 0) {
				canvas[plane_y--][plane_x] = 0;
				canvas[plane_y][plane_x] = 1;
			}
			break;
		}
		case ' ': {
			static int len, left, right;
			len = score / 5;
			left = plane_x - len > 0 ? plane_x - len : 0;
			right = plane_x + len < WIDTH - 1 ? plane_x + len : WIDTH - 1;
			for (i = left; i <= right; i++) {
				canvas[plane_y - 1][i] = 2;
			}
			break;
		}
		};
	}
}
