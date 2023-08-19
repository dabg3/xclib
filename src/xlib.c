#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include "xlib.h"

char * xitoa(int n, char *buffer, int radix) {
	if (radix < 2 || radix > 36) {
		errno = EINVAL;
		return NULL;
	}

char * xstrrev(char *str) {
	int len = xstrlen(str);
	for(int i = 0; i < len / 2; i++) {
		char tmp = str[i]; 
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
	}
	return str;
}

int xatoi(const char *str) {
	return 0;
}

int xstrlen(const char *str) {
	int c = 0;
	for(; *str; ++str, ++c) {}
	return c;
}
