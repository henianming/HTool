/*
[func(arg)]
*/

#include "file.h"

#define FUNC_COUNT_MAX 256
#define FUNC_NAME_MAX 256
#define FUNC_ARG_MAX 256

#define FMTFuncArg struct FMTFuncStruct *out, char const *in, int inF, int inT, char const *arg
typedef void(*FMTFunc)(struct FMTFuncStruct*, char const*, int, int, char const*);

#define FillNumRangeFuncArg int *outF, int *outT, char const *in, int inF, int inT

enum LOADSTATE {
	LOADSTATE_1,
	LOADSTATE_2,
	LOADSTATE_3,
	LOADSTATE_4,
};

enum FMTFUNC_PRIORITY {
	PRIORITY_NONE,			//高优先级

	PRIORITY_CONSTANT_S,
	PRIORITY_CONSTANT_N,
	PRIORITY_NUMBER,
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
	char arg[FUNC_ARG_MAX];
	int tail;
};

/*
exp:	aaaaabbb12bb
func:	[constant_s(ab)]
result:	4,6
*/
void CONSTANT_S(FMTFuncArg) {
	int l_F;
	int l_T;

	char temp[FUNC_ARG_MAX];

	memcpy(temp, in + inF, inT - inF);
	temp[inT - inF] = 0;

	char *temp2 = strstr(temp, arg);
	if (temp2) {
		l_F = inF + (temp2 - temp);
		l_T = l_F + strlen(arg);
	} else {
		l_F = -1;
		l_T = -1;
	}

	out->first = l_F;
	out->tail = l_T;
}

/*
exp:	aaaaabbb12bb
func:	[constant_n(0,3)]
result:	0,3
*/
void CONSTANT_N(FMTFuncArg) {
	int l_F;
	int l_T;

	sscanf(arg, "%d,%d", &l_F, &l_T);

	if (l_F < inF) {
		printf("CONSTANT_N() : (l_F = %d) < (inF = %d)\n", l_F, inF);
		l_F = inF;
	}

	if (l_T > inT) {
		printf("CONSTANT_N() : (l_T = %d) > (inT = %d)\n", l_T, inT);
		l_T = inT;
	}

	out->first = l_F;
	out->tail = l_T;
}

enum LOADNUMSTATE {
	LOADNUMSTATE_F,
	LOADNUMSTATE_T,
	LOADNUMSTATE_S,
};

/*
desc:	寻找字符串中的第一个英文数字
*/
void fillNumRange_en(FillNumRangeFuncArg) {
	int i;
	enum LOADNUMSTATE lns = LOADNUMSTATE_F;

	for (i = inF; i < inT; i++) {
		if (!(in[i] >= '0' && in[i] <= '9')) {
			*outF = -1;
			*outT = -1;
			return;
		}
	}

	*outF = inF;
	*outT = inT;
}

/*
desc:	寻找字符串中的第一个中文简体数字
*/
void fillNumRange_sc(FillNumRangeFuncArg) {

}

/*
desc:	寻找字符串中的第一个中文繁体数字
*/
void fillNumRange_tc(FillNumRangeFuncArg) {

}

int DecodeNum_en(char const *numStr) {
	int idx;
	sscanf(numStr, "%d", &idx);
	return idx;
}

int DecodeNum_sc(char const *numStr) {
	return -1;
}

int DecodeNum_tc(char const *numStr) {
	return -1;
}

int DecodeNum(struct FMTFuncStruct const *inFuncStruct, char const *in) {
	if (inFuncStruct->first == -1 || inFuncStruct->tail == -1) {
		return -1;
	}

	int numStyle;

	char numStrBuf[255];
	int numStrLen = inFuncStruct->tail - inFuncStruct->first;
	strncpy(numStrBuf, in + inFuncStruct->first, numStrLen);
	numStrBuf[numStrLen] = 0;

	sscanf(inFuncStruct->arg, "%d", &numStyle);

	switch (numStyle) {
	case 1:
		return DecodeNum_en(numStrBuf);
	case 2:
	case 3:
	default:
		break;
	}
	return -1;
}

void NUMBER(FMTFuncArg) {
	int l_F;
	int l_T;
	int numStyle;
	char l_arg[FUNC_NAME_MAX] = {0};

	sscanf(arg, "%d", &numStyle);

	switch (numStyle) {
	case 1:
		fillNumRange_en(&l_F, &l_T, in, inF, inT);
		break;
	case 2:
		fillNumRange_sc(&l_F, &l_T, in, inF, inT);
		break;
	case 3:
		fillNumRange_tc(&l_F, &l_T, in, inF, inT);
		break;
	default:
		break;
	}

	out->first = l_F;
	out->tail = l_T;
}

void INDEX(FMTFuncArg) {
	NUMBER(out, in, inF, inT, arg);
}

/*
exp:	aaaaabbb12bb
func:	[variable()]
result:	最大限度扩容
*/
void VARIABLE(FMTFuncArg) {
	out->first = inF;
	out->tail = inT;
}

int doFMTFunc(int *out, char const *in, struct FMTFuncStruct *fmtFuncStruct, int fmtFuncStructCount) {
	int i, j, k;
	int index = -1;

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
				if (fmtFuncStruct[k].tail != -1) {
					inF = fmtFuncStruct[k].tail;
					break;
				}
			}

			for (k = idx + 1; k < fmtFuncStructCount; k++) {
				if (fmtFuncStruct[k].first != -1) {
					inT = fmtFuncStruct[k].first;
					break;
				}
			}

			fmtFuncStruct[idx].func(fmtFuncStruct + idx, in, inF, inT, fmtFuncStruct[idx].arg);

			if (fmtFuncStruct[idx].func == INDEX) {
				index = DecodeNum(fmtFuncStruct + idx, in);
			}
		}
	}

	return index;
}

void fillFMTFuncRange(struct FMTFuncRange *out, int *outCount, char const *fmt) {
	char const *l_fmt = fmt;
	enum LOADSTATE ls = LOADSTATE_1;
	int funcCount = 0;

	while (*l_fmt != 0 && funcCount < FUNC_COUNT_MAX) {
		switch (ls) {
		case LOADSTATE_1:
			if (*l_fmt == '[') {
				out[funcCount]._1 = l_fmt - fmt;

				ls = LOADSTATE_2;
			}
			break;
		case LOADSTATE_2:
			if (*l_fmt == '(') {
				out[funcCount]._2 = l_fmt - fmt;

				ls = LOADSTATE_3;
			}
			break;
		case LOADSTATE_3:
			if (*l_fmt == ')') {
				out[funcCount]._3 = l_fmt - fmt;

				ls = LOADSTATE_4;
			}
			break;
		case LOADSTATE_4:
			if (*l_fmt == ']') {
				out[funcCount]._4 = l_fmt - fmt;

				funcCount++;
				ls = LOADSTATE_1;
			}
			else {
				ls = LOADSTATE_3;
			}
			break;
		}

		l_fmt++;
	}

	*outCount = funcCount;
}

void setFMTFuncStruct(struct FMTFuncStruct *out, char const *funcStr) {
	out->func = NULL;
	out->first = -1;
	out->tail = -1;
	if (strcmp("variable", funcStr) == 0) {
		out->func = VARIABLE;
		out->priority = PRIORITY_VARIABLE;
	} else if (strcmp("constant_n", funcStr) == 0) {
		out->func = CONSTANT_N;
		out->priority = PRIORITY_CONSTANT_N;
	} else if (strcmp("constant_s", funcStr) == 0) {
		out->func = CONSTANT_S;
		out->priority = PRIORITY_CONSTANT_S;
	} else if (strcmp("number", funcStr) == 0) {
		out->func = NUMBER;
		out->priority = PRIORITY_NUMBER;
	} else if (strcmp("index", funcStr) == 0) {
		out->func = INDEX;
		out->priority = PRIORITY_NUMBER;
	}
}

void fillFMTFuncStruct(struct FMTFuncStruct *out, struct FMTFuncRange const *in, int inCount, char const *fmt) {
	int i;

	for (i = 0; i < inCount; i++) {
		char funcStr[FUNC_NAME_MAX];
		unsigned int funcNameF = in[i]._1;
		unsigned int funcNameT = in[i]._2;
		unsigned int argF = in[i]._2;
		unsigned int argT = in[i]._3;
		memcpy(funcStr, fmt + funcNameF + 1, funcNameT - funcNameF - 1);
		memcpy(out[i].arg, fmt + argF + 1, argT - argF - 1);
		funcStr[funcNameT - funcNameF - 1] = 0;
		out[i].arg[argT - argF - 1] = 0;
		setFMTFuncStruct(out + i, funcStr);
	}
}

void fillOut(int *out, int *outCount, struct FMTFuncStruct *in, int inCount, int inLen) {
	int i;
	int j = 0;
	int prevIdxTail;

	for (i = 0; i < inCount; i++) {
		if ((j != 0) && (in[i].first != prevIdxTail)) {
			out[2 * j] = prevIdxTail;
			out[2 * j + 1] = in[i].first;
			j++;
		}

		out[2 * j] = in[i].first;
		out[2 * j + 1] = in[i].tail;
		prevIdxTail = in[i].tail;
		j++;

		if (i == (inCount - 1) && (in[i].tail != inLen)) {
			out[2 * j] = in[i].tail;
			out[2 * j + 1] = inLen;
			j++;
		}
	}

	*outCount = j;
}

int stringFmt(int *out, int *outCount, char const *in, char const *fmt) {
	int index;
	int funcCount = 0;
	struct FMTFuncRange fmtFuncRange[FUNC_COUNT_MAX];
	struct FMTFuncStruct fmtFuncStruct[FUNC_COUNT_MAX];

	fillFMTFuncRange(fmtFuncRange, &funcCount, fmt);

	fillFMTFuncStruct(fmtFuncStruct, fmtFuncRange, funcCount, fmt);

	int idxTemp = doFMTFunc(out, in, fmtFuncStruct, funcCount);
	index = idxTemp;

	fillOut(out, outCount, fmtFuncStruct, funcCount, strlen(in));
	return index;
}