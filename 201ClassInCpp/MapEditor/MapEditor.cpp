#include "pch.h"
#include <iostream>
#include <conio.h>
#include "../ClassInCpp/consts.h"
#include "../ClassInCpp/strutils.h"
#include "../ClassInCpp/consoleroutine.h"
#include "../ClassInCpp/tgeom.h"
#include "../ClassInCpp/tpoint.h"
#include "../ClassInCpp/trect.h"
#include "../ClassInCpp/tcircle.h"
#include "../ClassInCpp/list2link.h"

void printStatus1(short x, short y, short Left, short Top) {
	char *s = (char *)malloc(255 * sizeof(char));
	nullStr(s, 255);
	strcpy_s(s, 255, "F2=Save DEL=Delete F3=TPoint(Bank) F4=TPoint(House) F5=TPoint(Cafe) F6=TPoint(Shop) ");
	consoleSetColors(clBlack, clLightRed);
	consoleGotoXY(Left, Top);
	printf("x:3%d y:%3d      %s", x, y, s);
	free(s);
}

list2 *map_add_TPoint(list2 *map, short x, short y, TPointType t, 
	ConsoleColors color, ConsoleColors bgcolor) {
	TPoint *p = new TPoint();
	p->setX(x);
	p->setY(y);
	p->setColor(color);
	p->setBgColor(bgcolor);
	p->setTyp(t);

	list2 *result = list2_ins(map);
	result->geom = p;
	return result;
}

int main() {
	TRect *console = new TRect();
	console->setBounds(1, 1, consoleSizeY() - 2, consoleSizeX() - 2);
	
	TPoint *tank = new TPoint();
	tank->setX( console->getX() + console->getWidth()  / 2);
	tank->setY( console->getY() + console->getHeight() / 2);
	tank->setTyp(ptPen);
	tank->setColor(clLightGreen);
	tank->setBgColor(clLightGreen);

	list2 *map = NULL;

	int flagExit = 0;
	int keyPressed = 0;
	do {
		printStatus1(tank->getX(), tank->getY(), 0, 0);
		list2_print(map);
		tank->Print();
		consoleGotoXY(tank->getX(), tank->getY());
		keyPressed = _getch();
		switch (keyPressed) {
		    case KEY_ESCAPE: {
				flagExit = 1;
				break;
		    }
			case KEY_DELETE: {
				if (NULL != map) {
					list2 *p = list2_gotofirst(map);
					while (NULL != p) {
						if (1 == p->geom->Contains(tank->getX(), tank->getY())) {
							list2 *ptemp = p->next;
							if (p == list2_gotofirst(map)) {
								map = list2_gotolast(map);
							}
							if (p == list2_gotolast(map)) {
								map = list2_gotofirst(map);
							}
							if (1 == list2_count(map)) {
								map = NULL;
							}
							list2_del(p);
							p = ptemp;
						} else {
							p = p->next;
						}
					}
				}
				break;
			}
			case KEY_LEFT: {
				if (tank->getX() > console->getX()) {
					tank->setX( tank->getX() - 1 );
				}
				break;
			}
			case KEY_RIGHT: {
				if (tank->getX() < console->getWidth()) {
					tank->setX(tank->getX() + 1);
				}
				break;
			}
			case KEY_UP: {
				if (tank->getY() > console->getY()) {
					tank->setY(tank->getY() - 1);
				}
				break;
			}
			case KEY_DOWN: {
				if (tank->getY() < console->getHeight()) {
					tank->setY(tank->getY() + 1);
				}
				break;
			}
			case KEY_F2: {
				if (NULL != map) {
					list2_savetofile(map, "d:\\map.txt");
				}
				break;
			}
			case KEY_F3: {
				if (0 == list2_contains(map, tank->getX(), tank->getY())) {
					map = map_add_TPoint(map, tank->getX(), tank->getY(), ptBank, clBlack, clLightGreen);
				}
				break;
			}
			case KEY_F4: {
				if (0 == list2_contains(map, tank->getX(), tank->getY())) {
					map = map_add_TPoint(map, tank->getX(), tank->getY(), ptHouse, clWhite, clBrown);
				}
				break;
			}
			case KEY_F5: {
				if (0 == list2_contains(map, tank->getX(), tank->getY())) {
					map = map_add_TPoint(map, tank->getX(), tank->getY(), ptCafe, clWhite, clLightRed);
				}
				break;
			}
			case KEY_F6: {
				if (0 == list2_contains(map, tank->getX(), tank->getY())) {
					map = map_add_TPoint(map, tank->getX(), tank->getY(), ptShop, clBlack, clLightCyan);
				}
				break;
			}
		}
	} while (0 == flagExit);

	delete tank;
	//delete console;
	
	consoleSetColors(clWhite, clBlack);
	return 0;
}