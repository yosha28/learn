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
#include"../ClassInCpp/tcircle.h"

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
	else if (NULL != name) {
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

	tank->setY(console->getY() - 1);
	tank->setTyp(ptTank);
	tank->setColor(clBlack);
	tank->setBgColor(clLightRed);

	list2 *map = list2_loadfromfile(NULL, "d:\\map3.txt");
	list2_print(map);

	int flagExit = 0;
	int keyPressed = 0;
	list2 *findname = NULL;
	//TCircle *bum=NULL ;
	//TRect *bah=NULL ;

//	TCircle *bum = new TCircle();
//	TRect *bah = new TRect();


	do {

		printStatus1(tank->getX(), tank->getY(), 0, 0, list2_findmap(map, tank->getX(), tank->getY()));

		if (NULL != findname)
		{
			findname->geom->Print();
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
			if ((tank->getX() > console->getX())) {
				tank->setX(tank->getX() - 1);
			}
			else tank->setX(tank->getX());
			break;
		}
		case KEY_RIGHT: {
			if ((tank->getX() < console->getWidth())) {
				tank->setX(tank->getX() + 1);
			}
			else tank->setY(tank->getY());
			break;
		}
		case KEY_UP: {
			if ((tank->getY() > console->getY())) {
				tank->setY(tank->getY() - 1);
			}
			else tank->setY(tank->getY());
			break;
		}
		case KEY_DOWN: {
			if ((tank->getY() < console->getHeight())) {
				tank->setY(tank->getY() + 1);
			}
			else tank->setY(tank->getY());
			break;
		}

		case KEY_DELETE:
		{
			TCircle *bum = new TCircle();
			bum->setR(5);
			bum->setX(tank->getX());
			bum->setY(tank->getY());
			bum->setBgColor(clLightMagenta);
			bum->Print();

			if (NULL != map) {
				list2 *p = list2_gotofirst(map);
				while (NULL != p) {
					if (1 == bum->Contains(p->geom->getX(), p->geom->getY())) {
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
					}
					else {
						p = p->next;
					}
				}

			}
			// указатель на обект класса TCircle
			delete bum;
			break;
		}//удаление элементов  в пределах объекта прямоугольник
		case KEY_F9:
		{
			TRect *bah = new TRect();
			tank->setX(tank->getX() - 5);
			tank->setY(tank->getY() - 5);
			bah->setBounds(tank->getX(), tank->getY(), 10, 10);
			bah->setBgColor(clLightMagenta);//"красим" место взрыва
			bah->Print();//выводим на консоль
			tank->setX(tank->getX() + 5);
			tank->setY(tank->getY() + 5);
			if (NULL != map) {
				list2 *p = list2_gotofirst(map);
				while (NULL != p) {
					if (1 == bah->Contains(p->geom->getX(), p->geom->getY())) {
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
					}
					else {
						p = p->next;
					}
				}

			}
			delete bah;
			break;
		}
		}


	} while (0 == flagExit);

	delete tank;
	/*if (NULL != bah)
	{
		delete bah;
	}
	if (NULL != bum)
	{
		delete bum;
	}*/
	consoleGotoXY(0, consoleBuffSizeY() - 1);
	consoleSetColors(clWhite, clBlack);
	return 0;// gg Dortmund
}