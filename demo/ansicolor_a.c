#include <stdio.h>
#include <bbdump/ansicolor.h>

#define num(code) \
	fputs("  [" STYLE1(N(code), \
		"Sample text") "] " \
		ANSICOLOR_XSTR(code), stdout)

int main()
{
	/* Macro argument is stringified,
	 * and that's why there's no loop. */

	puts(STYLE1(BOLD, "Numbered styles (0-49)."));

	num(0); num(30); num(40); putchar('\n');
	num(1); num(31); num(41); putchar('\n');
	num(2); num(32); num(42); putchar('\n');
	num(3); num(33); num(43); putchar('\n');
	num(4); num(34); num(44); putchar('\n');
	num(5); num(35); num(45); putchar('\n');
	num(6); num(36); num(46); putchar('\n');
	num(7); num(37); num(47); putchar('\n');
	num(8); num(38); num(48); putchar('\n');
	num(9); num(39); num(49); putchar('\n');

	puts(STYLE1(BOLD, "Numbered styles (50-109)."));

	num(50); num(90); num(100); putchar('\n');
	num(51); num(91); num(101); putchar('\n');
	num(52); num(92); num(102); putchar('\n');
	num(53); num(93); num(103); putchar('\n');
	num(54); num(94); num(104); putchar('\n');
	num(55); num(95); num(105); putchar('\n');
	num(56); num(96); num(106); putchar('\n');
	num(57); num(97); num(107); putchar('\n');
	num(58); num(98); num(108); putchar('\n');
	num(59); num(99); num(109); putchar('\n');

	return 0;
}
