/* Take a byte and return a semicolon-separated list
 * of ANSI font style escape codes. */
const char *bytecolor_gray(int c);
const char *bytecolor_dim(int c);
const char *bytecolor_bright(int c);

/* Take a byte and return its ASCII representation. */
char asciichar(int c);
