// Registers the 0x122 plugin (fn_801520D0 with the three handlers, id kept in lbl_8042C820) and, if that succeeded, its follow-up callback; returns whether it did.

extern "C" {
extern unsigned char fn_8013D0BC[];
extern unsigned char fn_8013D0D8[];
extern unsigned char fn_8013D164[];
extern unsigned char fn_8013D274[];
extern int lbl_8042C820;
int fn_801520D0(int, int, void*, void*, void*);
void fn_8015218C(int, void*);

int fn_8013D2B8(void)
{
	lbl_8042C820 = fn_801520D0(0xc, 0x122, fn_8013D0BC, fn_8013D0D8, fn_8013D164);
	if (*(volatile int*)&lbl_8042C820 < 0) {
		return 0;
	}
	fn_8015218C(0x122, fn_8013D274);
	return 1;
}
}
