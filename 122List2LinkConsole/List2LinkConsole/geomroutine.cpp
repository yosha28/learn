#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "consoleroutine.h"
#include "geomroutine.h"

int PointInRect(   // возвращает "1", если точка внутри пр€моугольника, и "0" если не внутри
	short pointX,  // координата ’ точки
	short pointY,  // координата Y точки
	short left,    // координата X верхнего левого угла пр€моугольника
	short top,     // координата Y верхнего левого угла пр€моугольника
	short width,   // ширина пр€моугольника
	short height   // высота пр€моугольника
) {
	int result = 0;
	if ((pointX >= left) && (pointX <= (left + width))
		&& (pointY >= top) && (pointY <= (top + height))) {
		result = 1;
	}
	return result;
}

int PointInCircle(   // возвращает "1", если точка внутри окружности, и "0" если не внутри
	short pointX,  // координата ’ точки
	short pointY,  // координата Y точки
	short Xo,      // координата ’ центра окружности
	short Yo,      // координата Y центра окружности
	short radius   // радиус окружности
) {
	int result = 0;
	if (((Xo - pointX)*(Xo - pointX) + (Yo - pointY)*(Yo - pointY)) <= (radius*radius)) {
		result = 1;
	}
	return result;
}

void CirclePrint(short Xo, short Yo, short R) {
	consoleSetColors(clWhite, clWhite);
	for (int x = (Xo - R); x <= (Xo + R); x++) {
		for (int y = (Yo - R); y <= (Yo + R); y++) {
			if (1 == PointInCircle(x, y, Xo, Yo, R)) {
				consoleGotoXY(x, y);
				printf(" ");
			}
		}
	}
}

void CirclePrintClear(short Xo, short Yo, short R) {
	consoleSetColors(clBlack, clBlack);
	for (int x = (Xo - R); x <= (Xo + R); x++) {
		for (int y = (Yo - R); y <= (Yo + R); y++) {
			if (1 == PointInCircle(x, y, Xo, Yo, R)) {
				consoleGotoXY(x, y);
				printf(" ");
			}
		}
	}
}
void RectPrint(short left, short top, short height, short width) {
	consoleSetColors(clYellow, clYellow);
	for (int x = left; x <= (left + width); x++) {
		for (int y = top; y <= (top + height); y++) {
			consoleGotoXY(x, y);
			printf(" ");
		}
	}
}

void RectPrintClear(short left, short top, short height, short width) {
	consoleSetColors(clBlack, clBlack);
	for (int x = left; x <= (left + width); x++) {
		for (int y = top; y <= (top + height); y++) {
			consoleGotoXY(x, y);
			printf(" ");
		}
	}
}