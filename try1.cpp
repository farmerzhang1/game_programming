//从本章开始使用 graphics.h 
#include <graphics.h>
#include <conio.h>

int try1(void) {
	//X, Y, ...
	initgraph(500, 1000, NULL);
	setcolor(BLACK);//background color
	setfillcolor(BROWN);//fill color
	fillcircle(250, 500, 88);
	_getch();
	closegraph();
	return 0;
}
