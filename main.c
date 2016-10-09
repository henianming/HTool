#include "file.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>

#define CMDMAXLENGHT 1024
void ReName(char const *oldName, char const *newName) {
	char cmdStr[CMDMAXLENGHT];
	cmdStr[0] = 0;

	strcat(cmdStr, "RENAME \"");
	strcat(cmdStr, oldName);
	strcat(cmdStr, "\" \"");
	strcat(cmdStr, newName);
	strcat(cmdStr, "\"");

	system(cmdStr);
}

void MvFile(char const *srcPath, char const *desPath) {
	char cmdStr[CMDMAXLENGHT];
	cmdStr[0] = 0;

	strcat(cmdStr, "MOVE \"");
	strcat(cmdStr, srcPath);
	strcat(cmdStr, "\" \"");
	strcat(cmdStr, desPath);
	strcat(cmdStr, "\"");

	system(cmdStr);
}

void printFMT(char const *in, int const *idx, int idxCount) {
	int i;

	for (i = 0; i < idxCount; i++) {
		char *buf = (char*)malloc(idx[2 * i + 1] - idx[2 * i] + 1);

		memcpy(buf, in + idx[2 * i], idx[2 * i + 1] - idx[2 * i]);
		buf[idx[2 * i + 1] - idx[2 * i]] = 0;

		printf("%s ", buf);
		free(buf);
	}
	
	printf("\n");
}

struct fileInfo {
	int index;
	char name[260];
};

int main() {
	char *fmtFuncS = "[constant_s(Kai )][index(1)][constant_s( [DVDRip)]";
	char *fmtFuncD = "[constant_s(Ep.)][index(1)][constant_s( 「)]";
	char *srcFilePath = "F:\\新建文件夹 (4)\\";

	int i, j;
	int fmtedIdx[512];
	int fmtedCount;
	struct fileInfo infoBufS[1024];
	for (i = 0; i < 1024; i++) {
		infoBufS[i].name[0] = 0;
	}
	int sCount = 0;
	struct fileInfo infoBufD[1024];
	for (i = 0; i < 1024; i++) {
		infoBufD[i].name[0] = 0;
	}
	int dCount = 0;

	struct _finddata_t files;
	int File_Handle;
	char srcFileFullName[260];
	srcFileFullName[0] = 0;
	strcat(srcFileFullName, srcFilePath);
	strcat(srcFileFullName, "*");
	File_Handle = _findfirst(srcFileFullName, &files);
	if (File_Handle == -1) {
		printf("error\n");
		return;
	}
	do {
		int index = stringFmt(fmtedIdx, &fmtedCount, files.name, fmtFuncS);

		if (index != -1) {
			(infoBufS + sCount)->index = index;
			strcpy((infoBufS + sCount)->name, files.name);

			sCount++;
		}
	} while (0 == _findnext(File_Handle, &files));
	_findclose(File_Handle);

	File_Handle = _findfirst("F:\\[NAOKI-Raws] ひぐらしのなく頃に解 -When They Cry Kai- BD-BOX (BDRip x264 DTS-HDMA Chap)\\*", &files);
	if (File_Handle == -1) {
		printf("error\n");
		return;
	}
	do {
		int index = stringFmt(fmtedIdx, &fmtedCount, files.name, fmtFuncD);

		if (index != -1) {
			(infoBufD + dCount)->index = index;
			strcpy((infoBufD + dCount)->name, files.name);

			dCount++;
		}
	} while (0 == _findnext(File_Handle, &files));
	_findclose(File_Handle);

	for (i = 0; i < sCount; i++) {
		for (j = 0; j < dCount; j++) {
			if (infoBufS[i].index == infoBufD[j].index) {
				char fn[260];
				fn[0] = 0;
				strcat(fn, srcFilePath);
				strcat(fn, infoBufS[i].name);
				char *st = strrchr(fn, '.');
				char *dt = strrchr(infoBufD[j].name, '.');
				strcpy(dt, st);

				ReName(fn, infoBufD[j].name);
			}
		}
	}

	system("pause");
	return 0;
}