#include <stdio.h>
#include <stdlib.h>

int bounce(void) {
	int x = 10, y = 5;
	int up = 0, down = 50, left = 0, right = 50;
	int vx = 2, vy = 2;
	int i, j;
	while (1) {
		system("cls");
		if (x <= left || x >= right) {
			putchar('\a');
			vx *= -1;
		}
		if (y <= up || y >= down) {
			putchar('\a');
			vy *= -1;
		}
		x += vx;
		y += vy;
		for (i = 0; i < x; i++) putchar('\n');
		for (j = 0; j < y; j++) putchar(' ');
		putchar('H');
	}
	return 0;
}
