#include "CUnit/Basic.h"
#include <errno.h>
#include <string.h>
#include "xlib.h"

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void)
{
	return 0;	
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
	return 0;
}

void testxstrlen_validString(void) {
	char str[] = "abc";
	int res = xstrlen(str);
	CU_ASSERT(res == 3);
}

void testxstrlen_emptyString(void) {
	char str[] = "";
	int res = xstrlen(str);
	CU_ASSERT(res == 0);
}

void testxitoa_invalidRadix(void) {
	char str[16];
	int radix = 0;
	char *res = xitoa(1, str, radix);
	CU_ASSERT_FALSE(res);
	CU_ASSERT(errno == EINVAL);

	radix = 37;
	res = xitoa(1, str, radix);
	CU_ASSERT_FALSE(res);
	CU_ASSERT(errno == EINVAL);
}

void testxitoa_base2(void) {
	char str[16];
	char expected[] = "1010";
	char *res = xitoa(10, str, 2);
	CU_ASSERT(strcmp(res, expected) == 0);
}

void testxitoa_base16(void) {
	char str[16];
	char expected[] = "a";
	char *res = xitoa(10, str, 16);
	CU_ASSERT(strcmp(res, expected) == 0);
}

void testxitoa_base2neg(void) {
	char str[64];
	char expected[] = "11111111111111111111111111111000"; //two's complement (platform dependent)
	char *res = xitoa(-8, str, 2);
	CU_ASSERT(strcmp(res, expected) == 0);
}

void testxitoa_base10neg(void) {
	char str[64];
	char expected[] = "-8"; //two's complement (platform dependent)
	char *res = xitoa(-8, str, 10);
	CU_ASSERT(strcmp(res, expected) == 0);
}

void testxitoa_base16neg(void) {
	char str[16];
	char expected[] = "FFFFFFF8";
	char *res = xitoa(-8, str, 16);
	CU_ASSERT(strcmp(res, expected));
}

int main(void)
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	/* add a suite to the registry */
	pSuite = CU_add_suite("xlib", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	/* NOTE - ORDER IS IMPORTANT */
	if (
		(NULL == CU_add_test(pSuite, "xstrlen valid string", testxstrlen_validString)) ||
		(NULL == CU_add_test(pSuite, "xstrlen empty string", testxstrlen_emptyString)) ||
		(NULL == CU_add_test(pSuite, "xitoa invalid radix", testxitoa_invalidRadix)) ||
		(NULL == CU_add_test(pSuite, "xitoa base 2", testxitoa_base2)) ||
		(NULL == CU_add_test(pSuite, "xitoa base 2 negative", testxitoa_base2neg)) ||
		(NULL == CU_add_test(pSuite, "xitoa base 10 negative", testxitoa_base10neg)) ||
		(NULL == CU_add_test(pSuite, "xitoa base 16", testxitoa_base16)) ||
		(NULL == CU_add_test(pSuite, "xitoa base 16 negative", testxitoa_base16neg))
	) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
