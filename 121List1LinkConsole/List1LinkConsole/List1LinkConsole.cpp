#include "pch.h"
#include <iostream>
#include <conio.h>
#include "consoleroutine.h"
#include "geomroutine.h"
#include "tpointlist1.h"

int main() {
	TPoint *root = TPointCreate(0, 0, "", ptUnknown);
	TPoint *item = root;
	TPointInit(item);
	for (int i = 0; i < TPointCountTest; i++) {
		item = TPointAdd(item, 0, 0, "", ptUnknown);
		TPointInit(item);
	}

	short left   = 0;
	short top    = 0;
	short height = 0;
	short width  = 0;

	short xo = 0;
	short yo = 0;
	short r = 0;

	int key = 0;
	int flag = 0;
	do {
		TPointPrintToEnd(root);
		key = _getch();
		switch (key) {
		case KEY_F1:
			if ( (0 == left) && (0 == top) && (0== width) && (0 == height) ) {
				left = rand() % consoleSizeX() + 1;
				top = rand() % consoleSizeY() + 1;
				width = rand() % 8 + 10;
				height = rand() % 8 + 10;
				RectPrint(left, top, height, width);
				TPointSelectRect(root, left, top, height, width);
			} else {
				TPointSelectClear(root);
				RectPrintClear(left, top, height, width);
				left = 0;
				top = 0;
				height = 0;
				width = 0;
			}
			break;
		case KEY_F2:
			if ( (0 == xo) && (0 == yo) && (0 == r) ) {
				xo = rand() % consoleSizeX() + 1;
				yo = rand() % consoleSizeY() + 1;
				r  = rand() % 8 + 10;
				CirclePrint(xo, yo, r);
				TPointSelectCircle(root, xo, yo, r);
			} else {
				TPointSelectClear(root);
				CirclePrintClear(xo, yo, r);
				xo = 0;
				yo = 0;
				r  = 0;
			}
			break;
		case KEY_DELETE:
			TPointSelectClear(root);
			RectPrintClear(left, top, height, width);
			CirclePrintClear(xo, yo, r);
			break;
		case KEY_ESCAPE:
			flag = 1;
			break;
		}
	} while (0 == flag);
	
	TPointDelEnd(root);
	return 0;
}
