#include "file.h"
#include <stdio.h>
#include <stdlib.h>

void printFMT(char const *in, int const *idx, int idxCount) {
	int i;

	for (i = 0; i < idxCount; i++) {
		char *buf = (char*)malloc(idx[2 * i + 1] - idx[2 * i] + 1);

		memcpy(buf, in + idx[2 * i], idx[2 * i + 1] - idx[2 * i]);
		buf[idx[2 * i + 1] - idx[2 * i]] = 0;

		printf("%s ", buf);
		free(buf);
	}
}

int main() {
	char *fmtStr = "aaaaaaaabbbbbbbb";
	char *fmtFunc = "[constant_n(0,4)][constant_s(ab)][constant_n(9,11)]";
	int fmtedIdx[512];
	int fmtedCount;
	
	stringFmt(fmtedIdx, &fmtedCount, fmtStr, fmtFunc);

	printFMT(fmtStr, fmtedIdx, fmtedCount);

	while (1);
	return 0;
}