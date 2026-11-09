// Returns the entry [i][j] of the two-level table at lbl_8042C770, or the address
// of the fallback value when i is outside 0-9 or the table is missing.

extern "C" {
extern int*** lbl_8042C770;
extern int lbl_8042EE28;
int* fn_8012ECA8(int i, int j)
{
	if (i < 0 || i >= 10 || lbl_8042C770 == 0) {
		return &lbl_8042EE28;
	}
	return (int*)lbl_8042C770[i][j];
}
}
