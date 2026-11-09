// Reads the two words at index 4 and 5 of lbl_8028D2B8 into the given pointers
// (each optional) and returns 1.

extern "C" {
extern int lbl_8028D2B8[];
int fn_80158584(int* a, int* b)
{
	if (a != 0) {
		*a = lbl_8028D2B8[4];
	}
	if (b != 0) {
		*b = lbl_8028D2B8[5];
	}
	return 1;
}
}
