// When lbl_8042C9A0 is clear, runs the three init steps and clears +0x150 of lbl_8042C9A4; returns whether it ran.

extern "C" {
struct Glob8019DB0C {
	unsigned char pad[0x150];
	int f150;
};
extern int lbl_8042C9A0;
extern Glob8019DB0C* lbl_8042C9A4;
void fn_80198920(void);
void fn_80194218(void);
void fn_80197000(void);

int fn_8019DB0C(void)
{
	int t = (lbl_8042C9A0 == 0) ? 1 : 0;
	if (t != 0) {
		fn_80198920();
		fn_80194218();
		fn_80197000();
		lbl_8042C9A4->f150 = 0;
	}
	return t;
}
}
