// Creates the 0x18-byte pool into lbl_8042CF7C (fn_801966CC); returns arg0, or 0 when creation failed.

extern "C" {
extern unsigned char lbl_8040EB80[];
extern int lbl_8042C088;
extern int lbl_8042C08C;
extern unsigned lbl_8042CF7C;
unsigned fn_801966CC(int, int, int, int, void*);

int fn_8020BF9C(int a)
{
	int r        = a;
	lbl_8042CF7C = fn_801966CC(0x18, lbl_8042C088, 4, lbl_8042C08C, lbl_8040EB80);
	if (*(volatile unsigned*)&lbl_8042CF7C == 0) {
		r = 0;
	}
	return r;
}
}
