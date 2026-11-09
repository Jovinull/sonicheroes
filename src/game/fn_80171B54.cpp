// Runs fn_80170FDC on field 0x1D8 of the record at lbl_803EC968, destroys its free list at 0x1D4 and clears the pointer.

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
void fn_80170FDC(int);
void RwFreeListDestroy(void*);

void fn_80171B54()
{
	fn_80170FDC(lbl_803EC968.f1d8);
	RwFreeListDestroy(lbl_803EC968.f1d4);
	lbl_803EC968.f1d4 = 0;
}
}
