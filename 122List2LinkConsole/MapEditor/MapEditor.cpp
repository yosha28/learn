#include "pch.h"
#include <iostream>
#include <conio.h>
#include "../List2LinkConsole/consoleroutine.h"
#include "../List2LinkConsole/geomroutine.h"
#include "../List2LinkConsole/tpointlist2.h"

void printStatus1(short x, short y, short Left, short Top) {
	char *s = (char *)malloc(255 * sizeof(char));
	strcpy_s(s, 255, "F2=Save DEL=Delete F3=TPoint(Bank) F4=TPoint(House) F5=TPoint(Cafe) F6=TPoint(Shop) ");
	consoleSetColors(clBlack, clLightRed);
	consoleGotoXY(Left, Top);
	printf("x:3%d y:%3d      %s", x, y, s);
	free(s);
}

int main() {
	short conLeft   = 1;
	short conTop    = 1;
	short conHeight = consoleSizeY() - 2;
	short conWidth  = consoleSizeX() - 2;

	TPoint *pen = TPointCreate(0, conWidth / 2, conHeight / 2, "", "", ptTank);

	TPoint *map = NULL;

	int flagExit = 0;
	int keyPressed = 0;
	do {
		// выводим справочное сообщение
		printStatus1(pen->x, pen->y, 0, 0);
		// перерисовываем карту
		TPointPrint(map);
		// рисуем перо
		TPointPrintItem(pen);
		consoleGotoXY(pen->x, pen->y);
		// ждём нажатия клавиши
		keyPressed = _getch();
		// клавиша нажата, стираем перо с экрана
		consoleGotoXY(pen->x, pen->y);
		consoleSetColors(clBlack, clBlack);
		printf(" ");
		// обрабатываем нажатую клавишу
		switch (keyPressed) {
		case KEY_ESCAPE: {
			flagExit = 1;
			break;
		}
		case KEY_LEFT: {
			if (pen->x > conLeft) {
				pen->x--;
			}
			break;
		}
		case KEY_RIGHT: {
			if (pen->x < conWidth) {
				pen->x++;
			}
			break;
		}
		case KEY_UP: {
			if (pen->y > conTop) {
				pen->y--;
			}
			break;
		}
		case KEY_DOWN: {
			if (pen->y < conHeight) {
				pen->y++;
			}
			break;
		}
		case KEY_F2: {
			if (NULL != map) {
				TPointSaveToFile(map, "d:\\map.txt");
			}
			break;
		}
		case KEY_F3: {
			if (0 == TPointContains(map, pen->x, pen->y)) {
				map = TPointIns(map, 0, pen->x, pen->y, "", "", ptBank);
			}
			break;
		}
		case KEY_F4: {
			if (0 == TPointContains(map, pen->x, pen->y)) {
				map = TPointIns(map, 0, pen->x, pen->y, "", "", ptHouse);
			}
			break;
		}
		case KEY_F5: {
			if (0 == TPointContains(map, pen->x, pen->y)) {
				map = TPointIns(map, 0, pen->x, pen->y, "", "", ptCafe);
			}
			break;
		}
		}
	} while (0 == flagExit);

	free(pen);

	consoleSetColors(clWhite, clBlack);
	return 0;
}
