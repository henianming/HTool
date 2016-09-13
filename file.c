/*
[func(arg)]
*/

#include "file.h"

#define FUNC_COUNT_MAX 256
#define FUNC_NAME_MAX 256

#define FMTFuncArg struct FMTFuncStruct *out, char const *in, int inF, int inT, char const *arg
typedef void(*FMTFunc)(struct FMTFuncStruct*, char const*, int, char const*);

enum LOADSTATE {
	LOADSTATE_1,
	LOADSTATE_2,
	LOADSTATE_3,
	LOADSTATE_4,
};

enum FMTFUNC_PRIORITY {
	PRIORITY_NONE,			//高优先级

	PRIORITY_CONSTANT,
	PRIORITY_VARIABLE,

	PRIORITY_MAX,			//低优先级
};

struct FMTFuncRange {
	unsigned int _1;
	unsigned int _2;
	unsigned int _3;
	unsigned int _4;
};

struct FMTFuncStruct {
	int priority;
	int first;
	FMTFunc func;
	char arg[FUNC_NAME_MAX];
	int tail;
};

void VARIABLE(FMTFuncArg) {
	
}

void CONSTANT(FMTFuncArg) {

}

void setFMTFuncStruct(struct FMTFuncStruct *out, char const *funcStr) {
	out->func = NULL;
	out->first = -1;
	out->tail = -1;
	if (strcmp("variable", funcStr) == 0) {
		out->func = VARIABLE;
		out->priority = PRIORITY_VARIABLE;
	} else if (strcmp("constant", funcStr) == 0) {
		out->func = CONSTANT;
		out->priority = PRIORITY_CONSTANT;
	}
}

void doFMTFunc(char **out, char const *in, struct FMTFuncStruct *fmtFuncStruct, int fmtFuncStructCount) {
	int i, j, k;

	int fmtFuncIdxCount[PRIORITY_MAX - 1] = {0};
	int fmtFuncIdx[PRIORITY_MAX - 1][FUNC_COUNT_MAX] = {0};
	
	for (i = 0; i < fmtFuncStructCount; i++) {
		int l_fmtFuncIdx = fmtFuncStruct[i].priority - 1;
		fmtFuncIdx[l_fmtFuncIdx][fmtFuncIdxCount[l_fmtFuncIdx]] = i;
		fmtFuncIdxCount[l_fmtFuncIdx]++;
	}

	for (i = 0; i < PRIORITY_MAX - 1; i++) {
		for (j = 0; j < fmtFuncIdxCount[i]; j++) {

			int idx = fmtFuncIdx[i][j];
			int inF = 0;
			int inT = strlen(in);

			for (k = idx - 1; k >= 0; k--) {
				if (fmtFuncStruct[idx].tail != -1) {
					inF = fmtFuncStruct[idx].tail;
					break;
				}
			}

			for (k = idx + 1; k < fmtFuncStructCount; k++) {
				if (fmtFuncStruct[idx].first != -1) {
					inT = fmtFuncStruct[idx].first;
					break;
				}
			}

			fmtFuncStruct[idx].func(fmtFuncStruct + idx, in, inF, inT, fmtFuncStruct[idx].arg);
		}
	}
}

void stringFmt(char **out, int *outCount, char const *in, char const *fmt) {
	int i;
	int idx = 0;
	int funcCount = 0;
	struct FMTFuncRange fmtFuncRange[FUNC_COUNT_MAX];
	struct FMTFuncStruct fmtFuncStruct[FUNC_COUNT_MAX];
	char const *l_in = in;
	char const *l_fmt = fmt;
	enum LOADSTATE ls = LOADSTATE_1;

	while (*l_fmt != 0 && funcCount < FUNC_COUNT_MAX) {
		switch (ls) {
		case LOADSTATE_1:
			if (*l_fmt == '[') {
				fmtFuncRange[funcCount]._1 = idx;

				ls = LOADSTATE_2;
			}
			break;
		case LOADSTATE_2:
			if (*l_fmt == '(') {
				fmtFuncRange[funcCount]._2 = idx;

				ls = LOADSTATE_3;
			}
			break;
		case LOADSTATE_3:
			if (*l_fmt == ')') {
				fmtFuncRange[funcCount]._3 = idx;

				ls = LOADSTATE_4;
			}
			break;
		case LOADSTATE_4:
			if (*l_fmt == ']') {
				fmtFuncRange[funcCount]._4 = idx;

				funcCount++;
				ls = LOADSTATE_1;
			}
			break;
		}

		idx++;
		l_fmt++;
	}

	for (i = 0; i < funcCount; i++) {
		char funcStr[FUNC_NAME_MAX];
		int funcNameF = fmtFuncRange[i]._1;
		int funcNameT = fmtFuncRange[i]._2;
		int argF = fmtFuncRange[i]._2;
		int argT = fmtFuncRange[i]._3;
		memcpy(funcStr, fmt + funcNameF + 1, funcNameT - funcNameF - 1);
		memcpy(fmtFuncStruct[i].arg, fmt + argF + 1, argT - argF - 1);
		funcStr[funcNameT - funcNameF - 1] = 0;
		fmtFuncStruct[i].arg[argT - argF - 1] = 0;
		setFMTFuncStruct(fmtFuncStruct + i, funcStr);
	}

	doFMTFunc(out, in, fmtFuncStruct, funcCount);
}