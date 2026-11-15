extern "C" {
struct S {
	unsigned char pad[0x2C];
	int f2C;
};
extern S lbl_8029C310;
extern int lbl_80239F34[];
int fn_800A2D50(void)
{
	int v = lbl_8029C310.f2C;
	int cur;
	int i;
	for (i = 0; (cur = lbl_80239F34[i]) != -1; i++) {
		if (v == cur)
			return 1;
	}
	return 0;
}
}
