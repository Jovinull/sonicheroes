// Starts menu state 6 with slot k when idle and the slot at +0xD8+4k is 2; returns 1 once the menu was free, else 0.

extern "C" {
struct Menu80125664 {
	unsigned char pad[0x28];
	int f28;
	int f2c;
	char name[0x8c];
	int fbc;
	int fc0;
	unsigned char pad1[4];
	int fc8;
	unsigned char pad2[0xd8 - 0xcc];
	int d8[1];
	unsigned char pad3[0x268 - 0xdc];
	int f268;
	int f26c;
};
extern unsigned char lbl_803E774C[];
extern char lbl_8042B96C[4];
extern int lbl_8042C724;
int fn_8012822C(int);

int sprintf(char*, const char*, ...);

int fn_80125664(Menu80125664* o, int k)
{
	if (o->fbc == 0 && fn_8012822C(o->f28) == 0) {
		if (o->d8[k] == 2) {
			o->fbc       = 6;
			o->fc0       = 0;
			o->f268      = 0;
			lbl_8042C724 = 0;
			o->fc8       = k;
			sprintf(o->name, lbl_8042B96C, o->f26c, o->fc8);
		}
		return 1;
	}
	return 0;
}
}
