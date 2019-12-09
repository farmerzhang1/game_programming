#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define WIDTH 100
#define HEIGHT 40

void gotoxy(int, int);
void show(void);
void startup(void);
void without_input(void);

int i, j;
int cell[HEIGHT][WIDTH];


int main(void) {
	startup();
	while (1) {
		show();
		without_input();
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
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			cell[i][j] = rand() % 2;
		}
	}
}
void show(void) {
	gotoxy(0, 0);
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (cell[i][j]) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
}
void without_input(void) {
	static int tmp = 0;
	static int tmpcell[HEIGHT][WIDTH];
	//first line
	for (j = 1; j < WIDTH - 1 ; j++) {
		tmp = cell[0][j - 1] + cell[0][j + 1] + cell[1][j - 1] + cell[1][j] + cell[1][j + 1];
		if (tmp == 3) tmpcell[0][j] = 1;
		else if (tmp == 2) tmpcell[0][j] = cell[0][j];
		else tmpcell[0][j] = 0;
	}

	//second to last but one line
	for (i = 1; i < HEIGHT - 1; i++) {
		for (j = 1; j < WIDTH - 1; j++) {
			tmp = cell[i - 1][j - 1] + cell[i - 1][j] + cell[i - 1][j + 1] +
				cell[i][j - 1] + cell[i][j + 1] +
				cell[i + 1][j - 1] + cell[i + 1][j] + cell[i + 1][j + 1];
			if (tmp == 3) tmpcell[i][j] = 1;
			else if (tmp == 2) tmpcell[i][j] = cell[i][j];
			else tmpcell[i][j] = 0;
		}
	}

	//last line
	for (j = 1; j < WIDTH - 1; j++) {
		tmp = cell[HEIGHT - 1][j - 1] + cell[HEIGHT - 1][j + 1] + 
			cell[HEIGHT - 2][j - 1] + cell[HEIGHT - 2][j] + cell[HEIGHT - 2][j + 1];
		if (tmp == 3) tmpcell[HEIGHT - 1][j] = 1;
		else if (tmp == 2) tmpcell[HEIGHT - 1][j] = cell[HEIGHT - 1][j];
		else tmpcell[HEIGHT - 1][j] = 0;
	}

	//first column
	for (i = 1; i < HEIGHT - 1; i++) {
		tmp = cell[i - 1][0] + cell[i + 1][0] +
			cell[i - 1][1] + cell[i][1] + cell[i + 1][1];
		if (tmp == 3) tmpcell[i][0] = 1;
		else if (tmp == 2) tmpcell[i][0] = cell[i][0];
		else tmpcell[i][0] = 0;
	}

	//last column
	for (i = 0; i < HEIGHT - 1; i++) {
		tmp = cell[i - 1][WIDTH - 1] + cell[i + 1][WIDTH - 1] +
			cell[i - 1][WIDTH - 2] + cell[i][WIDTH - 2] + cell[i + 1][WIDTH - 2];
		if (tmp == 3) tmpcell[i][WIDTH - 1] = 1;
		else if (tmp == 2) tmpcell[i][WIDTH - 1] = cell[i][WIDTH - 1];
		else tmpcell[i][WIDTH - 1] = 0;
	}

	//copy temp cell to real cell
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			cell[i][j] = tmpcell[i][j];
		}
	}
}
