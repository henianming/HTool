/*
[func(arg)]
*/

#include "file.h"

#define FUNC_COUNT_MAX 256
#define FUNC_NAME_MAX 256

#define FMTFuncArg struct FMTFuncStruct *out, char const *in, int inLen, char const *arg
typedef void(*FMTFunc)(struct FMTFuncStruct*, char const*, int, char const*);

enum LOADSTATE {
	LOADSTATE_1,
	LOADSTATE_2,
	LOADSTATE_3,
	LOADSTATE_4,
};

enum FMTFUNC_PRIORITY {
	PRIORITY_CONSTANT,
	PRIORITY_VARIABLE,
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
	if (strcmp("variable", funcStr)) {
		out->func = VARIABLE;
		out->priority = PRIORITY_VARIABLE;
	} else if (strcmp("constant", funcStr)) {
		out->func = CONSTANT;
		out->priority = PRIORITY_CONSTANT;
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
		memcpy(funcStr, fmt + funcNameF + 1, funcNameT - funcNameF - 1);
		funcStr[funcNameT - funcNameF] = 0;
		setFMTFuncStruct(fmtFuncStruct + i, funcStr);
	}
}