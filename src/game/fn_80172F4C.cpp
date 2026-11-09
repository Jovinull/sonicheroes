// Creates the free list (fn_801966CC with 0x100, lbl_8042BDA0, 0x10, lbl_8042BDA4 and lbl_803ED3A8), stores it at 0x1DC of the record at lbl_803EC968 and returns 1.

extern "C" {
struct Rec968 {
	unsigned char pad[0x1d4];
	void* f1d4;
	int f1d8;
	int f1dc;
	unsigned char pad1[0x1e4 - 0x1e0];
	void* f1e4;
	void* f1e8;
};
extern Rec968 lbl_803EC968;
extern unsigned char lbl_803ED3A8[];
extern int lbl_8042BDA0;
extern int lbl_8042BDA4;
int fn_801966CC(int, int, int, int, void*);

int fn_80172F4C()
{
	lbl_803EC968.f1dc = fn_801966CC(0x100, lbl_8042BDA0, 0x10, lbl_8042BDA4, lbl_803ED3A8);
	return 1;
}
}
