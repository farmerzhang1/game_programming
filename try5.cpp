#include <graphics.h>
#include <conio.h>
int try5(void)
{
	int step = 30;
	initgraph(600, 600);
	setbkcolor(YELLOW);
	cleardevice();

	setlinestyle(PS_SOLID, 1); 
	setcolor(RGB(0, 0, 0)); 

	int i;
	for (i = 1; i <= 19; i++) 
	{
		line(i*step, 1 * step, i*step, 19 * step);
		line(1 * step, i*step, 19 * step, i*step);
	}
	_getch();
	closegraph();
	return 0;
}
