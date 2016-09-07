#include "file.h"

int main() {
	char *fmtedStr;
	int fmtedStrLen;
	stringFmt(&fmtedStr, &fmtedStrLen, "aaaaabbbbb", "aaaa[other()]");

	while (1);
	return 0;
}