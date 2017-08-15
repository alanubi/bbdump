#include <stdio.h>
#include <bbdump/ansicolor.h>

#define style(code) \
	fputs("  [" STYLE1(code, \
		"Sample text") "] " \
		#code, stdout)

int main()
{
	puts(STYLE1(BOLD, "Widely supported colors."));

	style(K); style(BG_K); putchar('\n');
	style(R); style(BG_R); putchar('\n');
	style(G); style(BG_G); putchar('\n');
	style(Y); style(BG_Y); putchar('\n');
	style(B); style(BG_B); putchar('\n');
	style(M); style(BG_M); putchar('\n');
	style(C); style(BG_C); putchar('\n');
	style(W); style(BG_W); putchar('\n');

	puts(STYLE1(BOLD, "Not widely supported colors."));

	style(KX); style(BG_KX); putchar('\n');
	style(RX); style(BG_RX); putchar('\n');
	style(GX); style(BG_GX); putchar('\n');
	style(YX); style(BG_YX); putchar('\n');
	style(BX); style(BG_BX); putchar('\n');
	style(MX); style(BG_MX); putchar('\n');
	style(CX); style(BG_CX); putchar('\n');
	style(WX); style(BG_WX); putchar('\n');

	puts(STYLE1(BOLD, "Widely supported font styles."));

	style(BOLD  ); putchar('\n');
	style(INVERT); putchar('\n');

	puts(STYLE1(BOLD, "Not widely supported font styles."));

	style(FAINT ); putchar('\n');
	style(ITALIC); putchar('\n');
	style(UNDER ); putchar('\n');
	style(SLOW  ); putchar('\n');
	style(RAPID ); putchar('\n');
	style(HIDDEN); putchar('\n');
	style(STRIKE); putchar('\n');

	puts(STYLE1(BOLD, "Special codes."));

	style(SHOW  ); putchar('\n');
	style(RESET ); putchar('\n');

	puts(STYLE1(BOLD, "Examples of multiple attributes."));

	puts("  [" STYLE0(
		"Sample text") "] "
		"0: -");

	puts("  [" STYLE2(BOLD, G,
		"Sample text") "] "
		"2: BOLD-G");

	puts("  [" STYLE3(STRIKE, INVERT, BG_B,
		"Sample text") "] "
		"3: STRIKE-INVERT-BG_B");

	puts("  [" STYLE4(UNDER, BOLD, INVERT, Y,
		"Sample text") "] "
		"4: UNDER-BOLD-INVERT-Y");

	puts("  [" STYLE2(STRIKE, UNDER, STYLE3(BOLD, C, BG_M,
		"Sample text")) "] "
		"2+3: STRIKE-UNDER-BOLD-C-BG_M");

	return 0;
}
