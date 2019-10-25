#ifndef TCIRCLE_H
#define TCIRCLE_H

#include "tgeom.h"

class TCircle :public TGeom {
public:
	short r;
	TCircle();
	virtual ~TCircle();
	virtual void InitTest();
	virtual int Contains(const short X, const short Y);
	virtual void Print();
	virtual void Erase();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
};

#endif