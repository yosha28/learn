#include "pch.h"
#include <iostream>
#include "consts.h"
#include "tgeom.h"
#include "tpoint.h"
#include "consoleroutine.h"

TPoint::TPoint() {
	TGeom::TGeom();
	setSymb('.');
	strcpy_s(name, defaultNameLength, "TPoint");
}

TPointType TPoint::getTyp() {
	return typ;
};

void TPoint::setTyp(const TPointType TYP) {
	if (TYP != typ) {
		Erase();
		typ = TYP;
	}
};

char TPoint::getSymb() {
	char s = TGeom::getSymb();
	switch (getTyp()) {
	   case ptBank : { s = 'B'; break; }
	   case ptHouse: { s = 'H'; break; }
	   case ptCafe : { s = 'C'; break; }
	   case ptShop : { s = 'S'; break; }
	   case ptTank : { s = 'T'; break; }
	   case ptPen  : { s = ' '; break; }
	}
	return s;
};