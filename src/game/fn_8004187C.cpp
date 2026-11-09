// Returns entry i (0-3) of the table lbl_80241CE8, or 0 for an index out of range.

extern "C" {
extern int lbl_80241CE8[];

int fn_8004187C(int i)
{
	if (i < 0 || i >= 4) {
		return 0;
	}
	return lbl_80241CE8[i];
}
}
