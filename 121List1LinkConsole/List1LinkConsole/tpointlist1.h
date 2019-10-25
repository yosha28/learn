#ifndef TPOINTLIST1_H
#define TPOINTLIST1_H

const int TPointNameLength =  20;
const int TPointCountTest  = 200;

enum TPointType {
   ptUnknown = 0
  ,ptBank    = 1
  ,ptCafe    = 2
  ,ptHouse   = 3
};

struct TPoint {
	short x;
	short y;
	char *name;
	short selected;
	TPointType typ;
	TPoint *next;
};

TPoint *TPointCreate(short x, short y, const char *name, TPointType typ);
TPoint *TPointAdd(TPoint *pred, short x, short y, const char *name, TPointType typ);
void TPointInit(TPoint *item);
TPoint *TPointDel(TPoint *p);
void TPointDelEnd(TPoint *fromPoint);
int TPointCount(TPoint *fromPoint);
void TPointPrint(TPoint *p);
void TPointPrintToEnd(TPoint *fromPoint);
void TPointSelectClear(TPoint *fromPoint);
void TPointSelectRect(TPoint *fromPoint, short left, short top, short height, short width);
void TPointSelectCircle(TPoint *fromPoint, short Xo, short Yo, short radius);

#endif