#include "pch.h"
#include <iostream>
#include "consts.h"
#include "strutils.h"

void nullStr(char *str, int count) {
	char *wrk = str;
	for (int i = 0; i < count; i++) {
		*wrk = 0;
		wrk++;
	}
}

char *parseItem(char *fromChar, const char delimiter, char *parsedItem) {
	nullStr(parsedItem, defaultNameLength);
	char *result = NULL;
	if (NULL != fromChar) {
		result = strchr(fromChar, delimiter); // ������� strstr ,� ���� ��� �� ������ �������� �����
		if (NULL != result) {
			for (int i = 0; i < (result - fromChar); i++) {
				*(parsedItem + i) = *(fromChar + i);
			}
			result++;
		}
	}
	return result;
}