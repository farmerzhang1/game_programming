#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
int try3(void) {
	initgraph(1400, 800, NULL);
	for (int y = 0; y < 800; y+=2) {
		setcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		line(0, y, 1500, y);
	}
	for (int x = 0; x < 1500; x+=2) {
		setcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		line(x, 0, x, 800);
	}
	_getch();
	closegraph();
	return 0;
}
