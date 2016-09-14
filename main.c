#include "file.h"

int main() {
	char *fmtedStr;
	int fmtedStrLen;
	stringFmt(&fmtedStr, &fmtedStrLen, "aaaaabbb12bb", "[constant_n(0,3)][variable()][constant_s(ab)]");

	while (1);
	return 0;
}