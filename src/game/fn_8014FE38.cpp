// Registers the 0xC/0x10 plugin (id kept in lbl_8042C8C8) and its second stage (lbl_8042C8CC); returns whether the second registration succeeded, 0 if the first failed.

extern "C" {
extern unsigned char fn_8014F4E4[];
extern unsigned char fn_8014F500[];
extern unsigned char fn_8014F504[];
extern unsigned char fn_8014F520[];
extern int lbl_8042C8C8;
extern unsigned lbl_8042C8CC;
int fn_8019D138(int, int, void*, void*, int);
unsigned fn_801541BC(int, int, void*, void*, int);

int fn_8014FE38(void)
{
	lbl_8042C8C8 = fn_8019D138(0xc, 0x10, fn_8014F4E4, fn_8014F500, 0);
	if (*(volatile int*)&lbl_8042C8C8 < 0) {
		return 0;
	}
	lbl_8042C8CC = fn_801541BC(0xc, 0x10, fn_8014F504, fn_8014F520, 0);
	return ((*(volatile unsigned*)&lbl_8042C8CC) >> 31) ^ 1;
}
}
