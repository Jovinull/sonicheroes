// Allocates the shared table on first use and counts the reference.
struct G80147998 {
	unsigned char pad0[4];
	int f4;
	int f8;
};

extern "C" {
extern G80147998 lbl_8028D1E8;
extern int lbl_8042BCE8;
extern int lbl_8042BCEC;
extern char lbl_803EC540[];
unsigned int fn_801966CC(int a, int b, int c, int d, char* e);
int fn_80142C20();

int fn_80147998(int a)
{
	if (lbl_8028D1E8.f4 == 0) {
		unsigned int r  = fn_801966CC(0x34, lbl_8042BCE8, 4, lbl_8042BCEC, lbl_803EC540);
		lbl_8028D1E8.f8 = r;
		if (r == 0) {
			return 0;
		}
		if (fn_80142C20() == 0) {
			return 0;
		}
	}
	lbl_8028D1E8.f4++;
	return a;
}
}
