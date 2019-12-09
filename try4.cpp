#include <graphics.h>
#include <conio.h>
int try4(void)
{
	int step = 50;
	initgraph(400, 400);
	setbkcolor(YELLOW);
	cleardevice();

	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 1)
			{
				setfillcolor(BLACK);
				solidrectangle(i*step, j*step, (i + 1)*step, (j + 1)*step); 
			}
			else
			{
				setfillcolor(WHITE);
				solidrectangle(i*step, j*step, (i + 1)*step, (j + 1)*step); 
			}
		}
	}
	_getch();
	closegraph();
	return 0;
}
