#include <stdio.h>
#include <bbdump/label.h>

int main()
{
	int value = 0;
Next:
	printf("%i: ", value);

	ENSURE (value % 2 == 0, odd);
	ENSURE (value % 4 == 0, even);
	puts("multiple of four");
	SKIP (even) puts("even");
	SKIP (odd) puts("odd");

	ENSURE (++value == 10, Next);

	return 0;
}
