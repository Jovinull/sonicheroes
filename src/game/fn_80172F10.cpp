// Destroys the free list held at 0x1DC of the record at lbl_803EC968 and clears the pointer.

extern "C" {
struct Rec80172F10 {
	unsigned char pad[0x1dc];
	void* f1dc;
};
extern Rec80172F10 lbl_803EC968;
void RwFreeListDestroy(void*);

void fn_80172F10()
{
	Rec80172F10* r = &lbl_803EC968;
	RwFreeListDestroy(r->f1dc);
	r->f1dc = 0;
}
}
