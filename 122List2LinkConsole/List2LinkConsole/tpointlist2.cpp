#include "pch.h"
#include <iostream>
#include "consoleroutine.h"
#include "geomroutine.h"
#include "tpointlist2.h"

TPoint *TPointCreate(
	int   id,
	short x,
	short y,
	const char *name,
	const char *addr,
	TPointType typ
) {
	TPoint *result = (TPoint *)malloc(sizeof(struct TPoint));
	result->name = (char *)malloc(TPointNameLength * sizeof(char));
	strcpy_s(result->name, TPointNameLength, name);
	result->addr = (char *)malloc(TPointNameLength * sizeof(char));
	strcpy_s(result->addr, TPointNameLength, addr);
	result->id       = id;
	result->x        = x;
	result->y        = y;
	result->typ      = typ;
	result->selected = 0;
	result->next     = NULL;
	result->pred     = NULL;
	return result;
}

TPoint *TPointIns(
	TPoint *pred,
	int   id,
	short x,
	short y,
	const char *name,
	const char *addr,
	TPointType typ
) {
	TPoint *result = TPointCreate(id, x, y, name, addr, typ);
	result->pred = pred;  // инициализация указателя предыдущего эл-та
	if (NULL != pred) {  // преверяем, существует ли предыдущий элемент (пустой список)
		result->next = pred->next;
		if (NULL != pred->next) { // проверяем, является ли предыдущий эл-т конечным или за ним есть ещё?
			pred->next->pred = result;
		}
		pred->next = result; // переопределение упредыдущего эл-та указателя следующего на себя
	}
	return (result);
}

void TPointDel(TPoint *item) {
	TPoint *nxt, *prv;
	if (NULL != item) {  // если элемент существует в памяти?
		nxt = item->next;  
		prv = item->pred;
		if (NULL != nxt) {   // не является ли элемент конечным в списке? 
			nxt->pred = item->pred;
		}
		if (NULL != prv) {   // не является ли элемент первым в списке?
			prv->next = item->next;
		}
		free(item->addr);
		free(item->name);
		free(item);
	}
}

TPoint *TPointFirst(TPoint *item) {
	TPoint *result = item;
	if (NULL != result) {
		while (NULL != result->pred) {
			result = result->pred;
		}
	}
	return result;
}

TPoint *TPointLast(TPoint *item) {
	TPoint *result = item;
	if (NULL != result) {
		while (NULL != result->next) {
			result = result->next;
		}
	}
	return result;
}

void TPointPrintItem(TPoint *item) {
	ConsoleColors clr;
	ConsoleColors bg = clBlack;
	char cp = ' ';
	if (NULL != item) {
		switch (item->typ) {
		    case ptUnknown: {
				clr = clBrown;       
				cp  = '?'; 
				break; 
			}
			case ptBank: {
				clr = clLightGreen;
				cp  = 'B';
				break;
			}
			case ptCafe: {
				clr = clLightMagenta;
				cp  = 'C';
				break; 
			}
			case ptHouse: {
				clr = clLightCyan;
				cp  = 'H';
				break;
			}
			case ptTank: {
				clr = clWhite;
				bg  = clGreen;
				cp  = 'T';
				break;
			}
		}
		if (0 != item->selected) {
			bg = clLightGrey;
		}
		consoleSetColors(clr, bg);
		consoleGotoXY(item->x, item->y);
		printf("%c", cp);
	}
};

void TPointPrint(TPoint *item) {
	TPoint *p = TPointFirst(item);
	while (NULL != p) {
		TPointPrintItem(p);
		p = p->next;
	}
};

int TPointContains(TPoint *item, short x, short y) {
	TPoint *p = TPointFirst(item);
	while (NULL != p) {
		if( (p->x == x) && (p->y == y) ) {
			return (1);
		}
		p = p->next;
	}
	return (0);
}

TPoint *TPointFindXY(TPoint *item, short x, short y) {
	TPoint *p = TPointFirst(item);
	while (NULL != p) {
		if ( (p->x == x) && (p->y == y) ) {
			return p;
		}
		p = p->next;
	}
	return p;
}

void TPointSave(FILE *fileHandle, TPoint *item) {
	fprintf(fileHandle, "%d|%d|%d|%d|%s|%s\n", item->id, item->x, item->y, (int)item->typ, item->name, item->addr);
}

void TPointSaveToFile(TPoint *item, const char *fileName) {
	FILE *fileToSave;
	TPoint *p = TPointFirst(item);
	int err = fopen_s(&fileToSave, fileName, "w+");
	if (0 == err) {
		while (NULL != p) {
			TPointSave(fileToSave, p);
			p = p->next;
		}
		fclose(fileToSave);
	}
}

void nullStr(char *str, int count) {
	char *wrk = str;
	for (int i = 0; i < count; i++) {
		*wrk = 0;
		wrk++;
	}
}

char *parseItem(char *fromChar, const char delimiter, char *parsedItem) {
	nullStr(parsedItem, 1024);
	char *result = NULL;
	if (NULL != fromChar) {
		result = strstr(fromChar, &delimiter);
		if (NULL != result) {
			for (int i = 0; i < (result - fromChar); i++) {
				*(parsedItem + i) = *(fromChar + i);
			}
			result++;
		}
	}
	return result;
}

TPoint *TPointLoadFromFile(TPoint *item, const char *fileName) {
	FILE *fileToLoad;
	TPoint *p = TPointLast(item);

	char *buffer  = (char *)malloc(1024 * sizeof(char));   // буфер для считывания из файла
	char *ch      = buffer;                                // рабочий указатель на ячейку памяти с символом  
	char *strId   = (char *)malloc(1024 * sizeof(char));   // буфер для id
	char *strX    = (char *)malloc(1024 * sizeof(char));   // буфер для x
	char *strY    = (char *)malloc(1024 * sizeof(char));   // буфер для y
	char *strType = (char *)malloc(1024 * sizeof(char));   // буфер для типа точки
	char *strName = (char *)malloc(1024 * sizeof(char));   // буфер для имени точки
	char *strAddr = (char *)malloc(1024 * sizeof(char));   // буфер для адреса
	char *parser  = NULL;

	int err = fopen_s(&fileToLoad, fileName, "r");
	if (0 == err) {
		nullStr(buffer, 1024);
		while (EOF != (*ch = fgetc(fileToLoad))) {
			if (*ch == '\n') {
				parser = buffer;
				parser = parseItem(parser, '|', strId);
				parser = parseItem(parser, '|', strX);
				parser = parseItem(parser, '|', strY);
				parser = parseItem(parser, '|', strType);
				parser = parseItem(parser, '|', strName);
				parser = parseItem(parser, '\n', strAddr);

				p = TPointIns(p, atoi(strId), atoi(strX), atoi(strY), strName, strAddr, (TPointType)atoi(strType));

				nullStr(buffer, 1024);
				ch = buffer;
			} else {
				ch++;
			}
		}
		fclose(fileToLoad);
	}
	free(strId);
	free(strX);
	free(strY);
	free(strType);
	free(strAddr);
	free(strName);
	free(buffer);
	return p;
}