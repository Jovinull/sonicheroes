// Starts menu state 1 when idle: takes the id from fn_80116B68, runs fn_80116D30, formats the name; returns whether it started.

extern "C" {
struct Menu801257D0 {
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
int fn_80116B68(void*);
void fn_80116D30(void*);

int sprintf(char*, const char*, ...);

int fn_801257D0(Menu801257D0* o)
{
	if (o->fbc == 0 && fn_8012822C(o->f28) == 0) {
		o->fbc       = 1;
		o->fc0       = 0;
		o->f268      = 0;
		lbl_8042C724 = 1;
		o->fc8       = fn_80116B68(lbl_803E774C);
		fn_80116D30(lbl_803E774C);
		sprintf(o->name, lbl_8042B96C, o->f26c, o->fc8);
		return 1;
	}
	return 0;
}
}
