#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int print_plane(int x);

int hit_plane(void) {
	int i, j;
	int x = 10;
	int y = 10;
	int nx = 0;//n means the ball
	int bound = 20;
	int nv = 1;//the velocity of the ball
	int HIT = 0;
	int FIRE = 0;
	char c;
	while (1) {
		system("cls");
		nx += nv;
		if (nx >= bound || nx <= 0) nv *= -1;
		if (HIT) {
			nv = 1;
			nx = 0;
			HIT = 0;
		}
		for (i = 0; i < nx; i++) putchar(' ');
		printf("$\n");
		if (FIRE) {
			for (j = 1; j < y; j++) {
				for (i = 0; i < x; i++) {
					putchar(' ');
				}
				printf("  |");
				putchar('\n');
				FIRE = 0;
			}
		}
		else {
			for (j = 1; j < y; j++)
			{
				putchar('\n');
			}
			for (i = 0; i < x; i++)
			{
				printf(" ");
			}
			putchar('\n');
		}
		print_plane(x);
		c = _getch();
		switch(c) {
		case 'w':y--; break;
		case 'a':x--; break;
		case 's':y++; break;
		case 'd':x++; break;
		case ' ':FIRE = 1; break;
		case 'q':return;
		};
		if (x + 2 == nx) HIT = 1;
	}
	return 0;
}

int print_plane(int x) {
	int i;
	for (i = 0; i < x + 2; i++) putchar(' ');
	printf("*");
	putchar('\n');
	for (i = 0; i < x; i++) putchar(' ');
	printf("*****");
	putchar('\n');
	for (i = 0; i < x + 1; i++) putchar(' ');
	printf("* *");
	putchar('\n');
}
