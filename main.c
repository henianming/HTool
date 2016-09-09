#include "file.h"

int main() {
	char *fmtedStr;
	int fmtedStrLen;
	stringFmt(&fmtedStr, &fmtedStrLen, "aaaaabbbbb", "[constant()]aaaa[variable()][constant()]");

	while (1);
	return 0;
}