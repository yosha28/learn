#include "pch.h"
#include <iostream>
#include <conio.h>
#include "../ClassInCpp/consts.h"
#include "../ClassInCpp/strutils.h"
#include "../ClassInCpp/consoleroutine.h"
#include "../ClassInCpp/tgeom.h"
#include "../ClassInCpp/tpoint.h"
#include "../ClassInCpp/trect.h"
#include "../ClassInCpp/list2link.h"

void printStatus1(short x, short y, short Left, short Top, list2 *name) {
	char *s = (char *)malloc(255 * sizeof(char));
	nullStr(s, 255);
	strcpy_s(s, 255, "F3=Load                               ");
	consoleSetColors(clBlack, clLightRed);
	consoleGotoXY(Left, Top);
	if (NULL == name)
	{
		printf("x:%3d y:%3d      %s ", x, y, s);
		
	}
	else if(NULL!= name) {
		printf("x:%3d y:%3d       %s", x, y, name->geom->name);
	}
	free(s);
}

int main() {
	setlocale(LC_ALL, "Russian");

	TRect *console = new TRect();
	console->setBounds(1, 1, consoleSizeY() - 2, consoleSizeX() - 2);

	TPoint *tank = new TPoint();
	tank->setX(console->getX() + console->getWidth() / 2);

	tank->setY(console->getY()-1);
	tank->setTyp(ptTank);
	tank->setColor(clBlack);
	tank->setBgColor(clLightRed);

	list2 *map = list2_loadfromfile(NULL, "d:\\map3.txt");
	list2_print(map);

	int flagExit = 0;
	int keyPressed = 0;
	list2 *findname = NULL;
	do {
		
		printStatus1(tank->getX(), tank->getY(), 0, 0, list2_findmap(map, tank->getX(), tank->getY()));
		
		if (NULL != findname)
		{
			findname->geom->Print();
			findname = NULL;
			printStatus1(tank->getX(), tank->getY(), 0, 0, NULL);
		}
		
		tank->Print();
		consoleGotoXY(tank->getX(), tank->getY());
		keyPressed = _getch();
		findname = list2_findmap(map, tank->getX(), tank->getY());
		switch (keyPressed) {
		case KEY_ESCAPE: {
			flagExit = 1;
			break;
		}
		case KEY_LEFT: {
			if ((tank->getX() > console->getX()) && (0 == list2_contains(map, (tank->getX() - 1), tank->getY()))) {
				tank->setX(tank->getX() - 1);
			}
			else tank->setX(tank->getX() - 1);
			break;
		}
		case KEY_RIGHT: {
			if ((tank->getX() < console->getWidth()) && (0 == list2_contains(map, (tank->getX() + 1), tank->getY()))) {
				tank->setX(tank->getX() + 1);
			}
			else tank->setX(tank->getX() + 1);
			break;
		}
		case KEY_UP: {
			if ((tank->getY() > console->getY()) && (0 == list2_contains(map, tank->getX(), (tank->getY() - 1)))) {
				tank->setY(tank->getY() - 1);
			}
			else tank->setY(tank->getY() - 1);
			break;
		}
		case KEY_DOWN: {
			if ((tank->getY() < console->getHeight()) && (0 == list2_contains(map, tank->getX(), (tank->getY() + 1)))) {
				tank->setY(tank->getY() + 1);
			}
			else tank->setY(tank->getY() + 1);
			break;
		}
		}
	} while (0 == flagExit);

	delete tank;
	//delete console;
	consoleGotoXY(0, consoleBuffSizeY() - 1);
	consoleSetColors(clWhite, clBlack);
	return 0;// gg Dortmund
}