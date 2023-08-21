#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>

/* Magic numbers for the algorithm */
// 64-bit architecture
static const unsigned long mask01 = 0x0101010101010101;
static const unsigned long mask80 = 0x8080808080808080;

#define LONGPTR_MASK (sizeof(long) - 1)

#define testbyte(x)                             \
	do {                                    \
		if (p[x] == '\0')               \
		return (p - str + x);		\
	} while (0)

int strlen_freebsd(const char *str)
{
	const char *p;
	const unsigned long *lp;
	long va, vb;

	lp = (const unsigned long *)((uintptr_t)str & ~LONGPTR_MASK);
	va = (*lp - mask01);
	vb = ((~*lp) & mask80);
	lp++;
	if (va & vb)
		/* Check if we have \0 in the first part */
		for (p = str; p < (const char *)lp; p++)
			if (*p == '\0')
				return (p - str);

	/* Scan the rest of the string using word sized operation */
	for (; ; lp++) {
		va = (*lp - mask01);
		vb = ((~*lp) & mask80);
		if (va & vb) {
			p = (const char *)(lp);
			testbyte(0);
			testbyte(1);
			testbyte(2);
			testbyte(3);
#if (LONG_BIT >= 64)
			testbyte(4);
			testbyte(5);
			testbyte(6);
			testbyte(7);
#endif
		}
	}
	/* NOTREACHED */
	return (0);
}



int main(void) {
	char *buf = malloc(1024 * 1024 * 256); //256mb
	int i;
	for (i = 0; i < 1024 * 1024 * 256; i++) {
		buf[i] = '0';
	}
	buf[i] = '\0';
	struct timeval tm1, tm2;
	size_t len = 0;
	gettimeofday(&tm1, NULL);
	len = strlen_freebsd(buf);
	gettimeofday(&tm2, NULL);
	long usec = (tm2.tv_sec * 1000000.0 + tm2.tv_usec) - 
		(tm1.tv_sec * 1000000.0 + tm1.tv_usec);
	printf("strlen_freebsd took: %ld usec (len: %ld)\n", usec, len);

	gettimeofday(&tm1, NULL);
	len = xstrlen(buf);
	gettimeofday(&tm2, NULL);
	usec = (tm2.tv_sec * 1000000.0 + tm2.tv_usec) - 
		(tm1.tv_sec * 1000000.0 + tm1.tv_usec);
	printf("xstrlen took: %ld usec (len: %ld)\n", usec, len);

	gettimeofday(&tm1, NULL);
	len = xstrlen0(buf);
	gettimeofday(&tm2, NULL);
	usec = (tm2.tv_sec * 1000000.0 + tm2.tv_usec) - 
		(tm1.tv_sec * 1000000.0 + tm1.tv_usec);
	printf("xstrlen0 took: %ld usec (len: %ld)\n", usec, len);

	free(buf);
}
