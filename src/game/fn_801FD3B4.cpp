// Merges the pending flags of the indexed entry into its active flags, clears the pending ones and returns the offset.
struct Q {
	unsigned char pad[0x3c];
	unsigned f3c;
	unsigned f40;
};
extern "C" {
extern int lbl_8042CF48;
int fn_801FD3B4(int a)
{
	Q* t   = *(Q**)(a + lbl_8042CF48);
	t->f40 = t->f40 | t->f3c;
	t->f3c = 0;
	return a;
}
}
