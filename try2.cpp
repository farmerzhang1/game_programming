#include <graphics.h>
#include <conio.h>

int try2(void) {
	initgraph(1000, 800, NULL);
	int step = 50;
	for (int y = 0; y < 800; y += step) {
		if (y / step % 2 == 0) setcolor(RGB(248, 24, 128));
		else setcolor(GREEN);
		line(0, y, 1000, y);
	}
	_getch();
	closegraph();
	return 0;
}
