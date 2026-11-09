// Marks slot arg0 of the table lbl_8042C860 as in use (after fn_80142E2C agrees); returns arg0, or 0 when it could not be taken.

extern "C" {
extern int lbl_8042C860;
unsigned fn_80142E2C(void);

int fn_80149214(int a)
{
	int t = lbl_8042C860;
	if (*(int*)(a + t) == 0) {
		if (fn_80142E2C() == 0) {
			return 0;
		}
		*(int*)(a + t) = 1;
	}
	return a;
}
}
