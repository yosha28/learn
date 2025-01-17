#ifndef TCIRCLE_H
#define TCIRCLE_H

#include "tgeom.h"

class TCircle :public TGeom {
private:
	short r;
public:
	TCircle();
	virtual ~TCircle();
	virtual short getR();
	virtual void setR(const short R);
	virtual void InitTest();
	virtual int Contains(const short X, const short Y);
	virtual void Print();
	virtual void Erase();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
};

#endif