// Creates the 0x1C-byte pool (fn_801966CC) into lbl_803EC968 +0x1D4, builds the active slot from it (+0x1D8) and initialises it; returns 1.

extern "C" {
struct Glob80171BA0 {
	unsigned char pad[0x1d4];
	int f1d4;
	int f1d8;
};
extern Glob80171BA0 lbl_803EC968;
extern unsigned char lbl_803ED380[];
extern int lbl_8042BD98;
extern int lbl_8042BD9C;
int fn_801966CC(int, int, int, int, void*);
int fn_80171620(int);
void fn_80171698(int);

int fn_80171BA0(void)
{
	lbl_803EC968.f1d4 = fn_801966CC(0x1c, lbl_8042BD98, 4, lbl_8042BD9C, lbl_803ED380);
	lbl_803EC968.f1d8 = fn_80171620(lbl_803EC968.f1d4);
	fn_80171698(lbl_803EC968.f1d8);
	return 1;
}
}
