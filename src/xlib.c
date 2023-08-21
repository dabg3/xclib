#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include "xlib.h"
#include <string.h>

//TODO: portability to platforms with int != 32 bit
static const unsigned long twocomplement_signbit_mask = 0x80000000;

char * xitoa(int n, char *buffer, int radix) {
	if (radix < 2 || radix > 36) {
		errno = EINVAL;
		return NULL;
	}
	if (n == 0) {
		buffer = "0";
		return buffer;
	}
	char alphabet[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int digits = 0;
	char prefix_sign = 0;
	unsigned int un = n;
	if (n < 0 && radix == 10) {
		un = n * -1;
		prefix_sign = '-';
	}
	for (; un > 0; un /= radix) {
		int rem = un % radix;
		buffer[digits] = alphabet[rem];
		digits++;
	}
	if (prefix_sign) {
		*(buffer + digits) = prefix_sign;
		digits++;
	}
	*(buffer + digits) = '\0';
	xstrrev(buffer);
	return buffer;
}

char * xstrrev(char *str) {
	int len = xstrlen0(str);
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
	uintptr_t *strp = str;
	long contains0 = 0;
	for (;
		(contains0 = (*strp - 0x0101010101010101) & ((~(*strp)) & 0x8080808080808080)) == 0; //TODO: portability
		strp++ 
	) {}
	int skipped_bytes = ((uint64_t)strp - (uint64_t)str);
	int lsb = ffsl(contains0);
	int len = (lsb / 8) - 1 + skipped_bytes;
	return len;
}

int xstrlen0(const char *str) {
	int c = 0;
	for(; *str; ++str, ++c) {}
	return c;
}
