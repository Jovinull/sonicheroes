// Clears the eight words of the table lbl_802911D4 (walking down from the end).

extern "C" {
extern int lbl_802911D4[];

void fn_801B1C9C(void)
{
	int* p     = lbl_802911D4 + 8;
	unsigned n = 8;
	goto check;
body:
	*p = 0;
check: {
	unsigned t = n;
	n--;
	p--;
	if (t != 0) {
		goto body;
	}
}
}
}
