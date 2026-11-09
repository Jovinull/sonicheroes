// Creates the 0x3C-byte pool into lbl_8042C988 (fn_801966CC); returns 0 on failure, otherwise clears lbl_8042C984 and returns 1.

extern "C" {
extern unsigned char lbl_803ED490[];
extern int lbl_8042BE10;
extern int lbl_8042BE14;
extern int lbl_8042C984;
extern unsigned lbl_8042C988;
unsigned fn_801966CC(int, int, int, int, void*);

int fn_80198860(void)
{
	lbl_8042C988 = fn_801966CC(0x3c, lbl_8042BE10, 4, lbl_8042BE14, lbl_803ED490);
	if (*(volatile unsigned*)&lbl_8042C988 == 0) {
		return 0;
	}
	lbl_8042C984 = 0;
	return 1;
}
}
