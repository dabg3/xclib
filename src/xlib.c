#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include "xlib.h"

char * xitoa(int n, char *buffer, int radix) {
	if (radix < 2 || radix > 36) {
		errno = EINVAL;
		return NULL;
	}
	char alphabet[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int digits = 0;
	if (n < 0) {
		n ^= 0x80000000;
	}
	for (; n > 0; n /= radix) {
		int rem = n % radix;
		buffer[digits] = alphabet[rem];
		digits++;
	}
	*(buffer + digits) = '\0';
	xstrrev(buffer);
	return buffer;
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
