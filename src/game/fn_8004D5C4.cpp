// Whether either of the first two words of the table at lbl_802B9080 (0 and 8)
// is set.

extern "C" {
extern int lbl_802B9080[];

int fn_8004D5C4(void)
{
	if (lbl_802B9080[2] != 0 || lbl_802B9080[0] != 0) {
		return 1;
	}
	return 0;
}
}
