// Registers the 0x122 plugin (fn_80152FDC with three handlers, id kept in lbl_8042C818) and its follow-up; returns whether registration succeeded.

extern "C" {
extern unsigned char fn_8013C248[];
extern unsigned char fn_8013C258[];
extern unsigned char fn_8013C2B0[];
extern unsigned char fn_8013C2B4[];
extern unsigned char fn_8013C660[];
extern unsigned char fn_8013C89C[];
extern int lbl_8042C818;
int fn_80152FDC(int, int, void*, void*, void*);
int fn_8015301C(int, void*, void*, void*);

int fn_8013C99C(void)
{
	lbl_8042C818 = fn_80152FDC(4, 0x122, fn_8013C248, fn_8013C258, fn_8013C2B0);
	if (*(volatile int*)&lbl_8042C818 < 0) {
		return 0;
	}
	return ((unsigned)fn_8015301C(0x122, fn_8013C2B4, fn_8013C660, fn_8013C89C) >> 31) ^ 1;
}
}
