#ifndef TPOINTLIST2_H
#define TPOINTLIST2_H

const int TPointNameLength = 50;

enum TPointType {
	 ptUnknown = 0
	,ptBank    = 1
	,ptCafe    = 2
	,ptHouse   = 3
	,ptTank    = 4
};

struct TPoint {
	int   id;
	char *name;
	char *addr;
	short x;
	short y;
	short selected;
	TPointType typ;
	TPoint *next;
	TPoint *pred;
};

TPoint *TPointCreate(
	     int   id, 
	     short x, 
	     short y, 
	     const char *name, 
	     const char *addr, 
	     TPointType typ
);

TPoint *TPointIns(
	     TPoint *pred, 
	     int id, 
	     short x, 
	     short y, 
	     const char *name, 
	     const char *addr, 
	     TPointType typ
);

void TPointDel(TPoint *item);
TPoint *TPointFirst(TPoint *item);
TPoint *TPointLast(TPoint *item);
void TPointPrintItem(TPoint *item);
void TPointPrint(TPoint *item);
int TPointContains(TPoint *item, short x, short y);
TPoint *TPointFindXY(TPoint *item, short x, short y);

void TPointSave(FILE *fileHandle, TPoint *item);
void TPointSaveToFile(TPoint *item, const char *fileName);
TPoint *TPointLoadFromFile(TPoint *item, const char *fileName);

#endif