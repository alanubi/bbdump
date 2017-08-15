#include <stdio.h>
#include <bbdump/switch.h>
#include <bbdump/label.h>

int main()
{
	int value = 0;
	do {
		int square;

		switch (value) {
		when (0)  fputs("Zero", stdout);
		when (1)  fputs("One" , stdout);
		when (2)  fputs("Two" , stdout);
		otherwise fputs("Many", stdout);
		}

		square = value * value;
		ENSURE (square <= 5, endloop);
		puts(" <= sqrt(5)");

		++value;
	} LOOP (endloop);
	puts(" > sqrt(5)");

	return 0;
}
