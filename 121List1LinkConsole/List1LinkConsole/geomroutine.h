#ifndef GEOMROUTINE_H
#define GEOMROUTINE_H

int PointInRect(   // возвращает "1", если точка внутри пр€моугольника, и "0" если не внутри
	short pointX,  // координата ’ точки
	short pointY,  // координата Y точки
	short left,    // координата X верхнего левого угла пр€моугольника
	short top,     // координата Y верхнего левого угла пр€моугольника
	short width,   // ширина пр€моугольника
	short height   // высота пр€моугольника
);

int PointInCircle( // возвращает "1", если точка внутри окружности, и "0" если не внутри
	short pointX,  // координата ’ точки
	short pointY,  // координата Y точки
	short Xo,      // координата ’ центра окружности
	short Yo,      // координата Y центра окружности
	short radius   // радиус окружности
);

void CirclePrint(short Xo, short Yo, short R);
void CirclePrintClear(short Xo, short Yo, short R);
void RectPrint(short left, short top, short height, short width);
void RectPrintClear(short left, short top, short height, short width);

#endif