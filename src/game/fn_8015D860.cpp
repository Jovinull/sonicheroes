// Fills the object's four-entry callback table (at 0x14) and returns 1.

extern "C" {
void fn_8015D5E8();
void fn_8015D4C4();
void fn_8015C090();
struct Obj15D860 {
	unsigned char pad[0x14];
	void (**table)();
};
int fn_8015D860(Obj15D860* o)
{
	void (**t)() = o->table;
	t[0]         = fn_8015D5E8;
	t[1]         = 0;
	t[2]         = fn_8015D4C4;
	t[3]         = fn_8015C090;
	return 1;
}
}
