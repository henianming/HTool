/*
[func(arg)]
*/

#include "file.h"

enum LOADSTATE {
	LOADSTATE_1,
	LOADSTATE_2,
	LOADSTATE_3,
	LOADSTATE_4,
};

void stringFmt(char **out, int *outLen, char const *in, char const *fmt) {
	char const *l_in = in;
	char const *l_fmt = fmt;
	enum LOADSTATE ls = LOADSTATE_1;

	while (*l_fmt != 0) {
		switch (ls) {
		case LOADSTATE_1:
			if (*l_fmt == '[') {

				ls = LOADSTATE_2;
			}
			break;
		case LOADSTATE_2:
			if (*l_fmt == '(') {

				ls = LOADSTATE_3;
			}
			break;
		case LOADSTATE_3:
			if (*l_fmt == ')') {

				ls = LOADSTATE_4;
			}
			break;
		case LOADSTATE_4:
			if (*l_fmt == ']') {

				ls = LOADSTATE_1;
			}
			break;
		}
		
		l_fmt++;
	}
}