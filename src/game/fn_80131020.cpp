// Locks the manager lbl_8042C1F8 with arg0, creates an entry (arg1, type 0x11), stores arg2 at +0x14, unlocks and returns the entry.

extern "C" {
struct Entry80131020 {
	unsigned char pad[0x14];
	int f14;
};
extern int lbl_8042C1F8;
void fn_8004CC3C(int);
void fn_8004CC7C(int, int);
Entry80131020* fn_8004E408(int, int, int);

Entry80131020* fn_80131020(int a, int b, int c)
{
	Entry80131020* t;
	fn_8004CC7C(lbl_8042C1F8, a);
	t      = fn_8004E408(lbl_8042C1F8, b, 0x11);
	t->f14 = c;
	fn_8004CC3C(lbl_8042C1F8);
	return t;
}
}
