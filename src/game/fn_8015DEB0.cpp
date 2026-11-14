// Registers the handler set (fn_8015DE98, fn_8015DEA8, fn_8015DEAC) with fn_801541BC as kind
// 0x1C, id 0x505, keeps the result in lbl_8042C940 and returns whether it is non-negative (the
// handle is re-read after the store, so it is declared volatile).
extern "C" {
extern volatile int lbl_8042C940;
void fn_8015DE98(void);
void fn_8015DEA8(void);
void fn_8015DEAC(void);
int fn_801541BC(int kind, int id, void (*a)(void), void (*b)(void), void (*c)(void));

int fn_8015DEB0(void)
{
	lbl_8042C940 = fn_801541BC(0x1C, 0x505, fn_8015DE98, fn_8015DEA8, fn_8015DEAC);
	return lbl_8042C940 < 0 ? 0 : 1;
}
}
