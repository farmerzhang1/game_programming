#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

void startup(void);
void show(void);
void without_input(void);
void with_input(void);
void gotoxy(int, int);
void HideCursor();

/*global variables*/
int position_x, position_y;// x responds to width, y responds to height
const int width = 40;
const int height = 20;
int bullet_x, bullet_y;
int score;
int i, j;
int alien_x, alien_y;

int main(void) {
	startup();
	while (1) {
		show();
		without_input();
		with_input();
	}
	return 0;
}

void startup(void) {//initialize some values
	position_x = width / 2;
	position_y = 0;
	bullet_x = -1;
	bullet_y = -1;
	score = 0;
	alien_x = rand() % width;
	alien_y = 0;
	HideCursor();
}

void show(void) {
	gotoxy(0, 0);
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			if (i == position_x && j == position_y) {
				printf("*");
			}
			else if (i == bullet_x && j == bullet_y) {
				printf("|");
			}
			else if (i == alien_x && j == alien_y) {
				printf("@");
			}
			else printf(" ");
		}
		printf("\n");
	}
	printf("score:\t%d", score);
}

void with_input(void) {
	int c;
	if (_kbhit()) {//use this, so you don't have to wait for every keyboard movement
		c = _getch();
		switch (c) {
		case 'a': {
			if (position_x > 0) position_x--;
			break;
		}
		case 's': {
			if (position_y < height) position_y++;
			break;
		}
		case 'd': {
			if (position_x < width) position_x++;
			break;
		}
		case 'w': {
			if (position_y > 0) position_y--;
			break;
		}
		case ' ': {
			bullet_x = position_x;
			bullet_y = position_y;
		}
		};
	}
}

void without_input(void) {
	static int ping = 0;
	if (bullet_y >= 0) bullet_y--;
	if (alien_x == bullet_x && alien_y == bullet_y) {
		alien_x = rand() % width;
		alien_y = 0;
		bullet_x = -1;
		bullet_y = -1;
		score++;
	}
	else if (alien_y >= height) {
		alien_x = rand() % width;
		alien_y = 0;
		score -= 5;
		if (score < 0) score = 0;
	}
	else if (alien_x == position_x && alien_y == position_y) {
		alien_x = rand() % width;
		alien_y = 0;
		score -= 5;
		if (score < 0) score = 0;
	}
	if (ping == 10){
		alien_y++;
		ping = 0;
	}
	else
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

void HideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
