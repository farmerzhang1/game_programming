#include <stdio.h>
#include <graphics.h>
#include <conio.h>

void mouse(void) {
	initgraph(500, 500, NULL);
	MOUSEMSG mouse;
	while (1) {
		mouse = GetMouseMsg();
		if (mouse.uMsg == WM_MOUSEMOVE)
			putpixel(mouse.x, mouse.y, GREEN);
		else if (mouse.uMsg == WM_LBUTTONDOWN)
			fillcircle(mouse.x, mouse.y, 5);
		else if (mouse.uMsg == WM_RBUTTONUP)
			rectangle(mouse.x - 5, mouse.y - 5, mouse.x + 5, mouse.y + 5);
	}
}
