#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

void startup(void);
void show(void);
void without_input(void);
void with_input(void);
void gotoxy(int, int);
void HideCursor(void);

int i, j;
int ball_x, ball_y;
int bar_left, bar_len;
const int height = 20, width = 50;
int ball_vx, ball_vy;
int score;
int bar_y;
int HIT = 0;


int main(void) {
	startup();
	while (!HIT) {
		show();
		without_input();
		with_input();
	}
	show();
	printf("you lose!!!!\nHHHHH\n");	
	system("pause");
}

void startup(void) {
	score = 0;
	ball_x = width / 2;
	ball_y = 0;
	bar_left = width / 3;
	bar_len = width / 5;
	bar_y = height - 1;
	ball_vx = 1;
	ball_vy = 1;
	HideCursor();
}

void show(void) {
	gotoxy(0, 0);
	for (j = 0; j <= height; j++) {
		for (i = 0; i <= width; i++) {
			if (i == width) {
				printf("|");
			}
			else if (j == height) {
				printf("_");
			}
			else if ((i >= bar_left && i <= bar_left + bar_len) && (j == bar_y)) {
				printf("*");
			}
			else if (i == ball_x && j == ball_y) {
				printf("O");
			}
			else printf(" ");
		}
		printf("\n");
	}
	printf("your score: %d\n", score);
}

void without_input(void) {
	static int ping = 0;
	if (ping == 3) {
		ball_x += ball_vx;
		ball_y += ball_vy;
		if (ball_x <= 0 || ball_x >= width - 1) {
			ball_vx *= -1;
		}
		if (ball_y <= 0 || ball_y >= height) {
			ball_vy *= -1;
		}
		ping = 0;
	}
	if (ball_y == bar_y && (ball_x <= bar_left + bar_len) && ball_x >= bar_left) {
		score++;
		ball_vy *= -1;
	}
	else if (ball_y == height) {
		HIT = 1;
	}
	ping++;
}

void with_input(void) {
	int c;
	if (_kbhit()) {
		c = _getch();
		switch (c) {
		case 'a': {
			if (bar_left > 0)bar_left--;
			break;
		}
		case 'd': {
			if (bar_left + bar_len < width - 1) bar_left++;
			break;
		}
		};
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

void HideCursor(void)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
