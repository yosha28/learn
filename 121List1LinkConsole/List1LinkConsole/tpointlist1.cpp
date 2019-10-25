#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "consoleroutine.h"
#include "geomroutine.h"
#include "tpointlist1.h"


TPoint *TPointCreate(short x, short y, const char *name, TPointType typ) {
	TPoint *item = (TPoint *)malloc(sizeof(struct TPoint));
	item->x = x;
	item->y = y;
	item->typ = typ;
	item->selected = 0;
	item->name = (char *)malloc(TPointNameLength * sizeof(char));
	strcpy_s(item->name, TPointNameLength, name);
	item->next = NULL;
	return item;
}

TPoint *TPointAdd(TPoint *pred, short x, short y, const char *name, TPointType typ) {
	TPoint *item = TPointCreate(x, y, name, typ);
	TPoint *save = NULL;
	if (NULL != pred) {
		save = pred->next;
		pred->next = item;
	}
	item->next = save;
	return item;
}

void TPointInit(TPoint *item) {
	if (NULL != item) {
		item->x = rand() % consoleSizeX() + 1;
		item->y = rand() % consoleSizeY() + 1;
		switch (rand() % 3) {
		case 0: item->typ = ptBank; break;
		case 1: item->typ = ptCafe; break;
		case 2: item->typ = ptHouse; break;
		}
	}
}

TPoint *TPointDel(TPoint *p) {
	TPoint *next = NULL;
	if (NULL != p) {
		next = p->next;
		free(p->name);
		free(p);
	}
	return next;
}

void TPointDelEnd(TPoint *fromPoint) {
	TPoint *next = NULL;
	if (NULL != fromPoint) {
		next = fromPoint->next;
		while (NULL != next) {
			next = TPointDel(next);
		}
		TPointDel(fromPoint);
	}
}

int TPointCount(TPoint *fromPoint) {
	int result = 0;
	TPoint *item = fromPoint;
	while (NULL != item) {
		result++;
		item = item->next;
	}
	return result;
}

void TPointPrint(TPoint *p) {
	ConsoleColors clr;
	ConsoleColors bg = clBlack;
	char cp = ' ';
	if (NULL != p) {
		switch (p->typ) {
		case ptUnknown: clr = clBrown;       cp = '?'; break;
		case ptBank: clr = clLightGreen;  cp = 'B'; break;
		case ptCafe: clr = clLightMagenta; cp = 'C'; break;
		case ptHouse: clr = clLightCyan;   cp = 'H'; break;
		}
		if (0 != p->selected) {
			bg = clLightGrey;
		}
		consoleSetColors(clr, bg);
		consoleGotoXY(p->x, p->y);
		printf("%c", cp);
	}
}

void TPointPrintToEnd(TPoint *fromPoint) {
	TPoint *p = fromPoint;
	while (NULL != p) {
		TPointPrint(p);
		p = p->next;
	}
}

void TPointSelectClear(TPoint *fromPoint) {
	TPoint *p = fromPoint;
	while (NULL != p) {
		if (NULL != p->next) {
			if (1 == p->next->selected) {
				p->next = TPointDel(p->next);
			}
		}
		p = p->next;
	}
}

void TPointSelectRect(TPoint *fromPoint, short left, short top, short height, short width) {
	TPoint *p = fromPoint;
	while (NULL != p) {
		p->selected = PointInRect(p->x, p->y, left, top, width, height);
		p = p->next;
	}
}

void TPointSelectCircle(TPoint *fromPoint, short Xo, short Yo, short radius) {
	TPoint *p = fromPoint;
	while (NULL != p) {
		p->selected = PointInCircle(p->x, p->y, Xo, Yo, radius);
		p = p->next;
	}
}