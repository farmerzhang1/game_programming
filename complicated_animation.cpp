#include <graphics.h>
#include <conio.h>

int main(void) {
	initgraph(480, 300);
	IMAGE img_human, img_walls;
	loadimage(&img_human, "D:\\animation\\walking_man.jpg");
	loadimage(&img_walls, "D:\\animation\\walls.gif");
	int x, y; 
	int maps[8][5] = { 0 };
	for (int i = 0; i < 8; i++) {
		maps[i][0] = 1;
		maps[i][4] = 1;
	}
	for (int j = 0; j < 5; j++) {
		maps[0][j] = 1;
		maps[7][j] = 1;
	}
	x = 250;
	y = 80;
	int left_i = 0;
	int right_i = 0; 
	char input;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 5; j++) {
			if (maps[i][j]) putimage(i * 60, j * 60, &img_walls);
			putimage(x, y, 75, 130, &img_human, 0, 0);
		}
	}
	while (1) {
		if (_kbhit()) {
			input = _getch();
			if (input == 'a' || input == 'A') {
				clearrectangle(x, y, x + 75, y + 130);
				left_i++;
				if (x > 60) x -= 10;
				putimage(x, y, 75, 130, &img_human, left_i * 75, 0);
				FlushBatchDraw();
				if (left_i == 3) left_i = 0;
			}
			else if (input == 'd' || input == 'D') {
				clearrectangle(x, y, x + 75, y + 130);
				right_i++;
				if (x < 340) x += 10;
				putimage(x, y, 75, 130, &img_human, right_i * 75, 120);
				FlushBatchDraw();
				if (right_i == 3) right_i = 0;
			}
		}
	}
}
