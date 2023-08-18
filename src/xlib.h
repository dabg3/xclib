/** 
 * Convert int into a string.
 *
 * @param n Value to be converted to a string
 * @param buffer Array where the conversion result is stored
 * @param radix Number of unique digits used to represent `n` as a string
 * @return pointer to array containing the result, same as `buffer`
 */
char * xitoa(int n, char *buffer, int radix);

int xatoi(const char *str);


/** 
 * calculate the length of a string.
 *
 * The strlen() function calculates the length of the string s, 
 * excluding the terminating null byte
 *
 * @param 
 */
int xstrlen(const char *str);
