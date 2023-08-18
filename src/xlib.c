#include <stdint.h>
#include <stdio.h>
#include "xlib.h"

char * xitoa(int n, char *buffer, int radix) {

}

int xatoi(const char *str) {
	return 0;
}

int xstrlen(const char *str) {
	int c = 0;
	for(c = 0; *str != '\0' || *str != EOF; c++) {}
	return c;
}
