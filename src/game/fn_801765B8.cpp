// Destroys the two free lists at 0x1E4 and 0x1E8 of the record at lbl_803EC968 and clears the pointers.

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
void RwFreeListDestroy(void*);

void fn_801765B8()
{
	RwFreeListDestroy(lbl_803EC968.f1e4);
	RwFreeListDestroy(lbl_803EC968.f1e8);
	lbl_803EC968.f1e4 = 0;
	lbl_803EC968.f1e8 = 0;
}
}
