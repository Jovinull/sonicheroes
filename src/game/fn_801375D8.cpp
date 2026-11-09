// Destructor: stores the class vtable at 0x18, clears lbl_8042C7D8, runs dtor_80136EA8 and frees the object when the delete flag is positive.

extern "C" {
struct Obj801375D8 {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char lbl_8028B0B0[];
extern int lbl_8042C7D8;
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void dtor_80136EA8(void*, int);

Obj801375D8* fn_801375D8(Obj801375D8* o, short flags)
{
	if (o != 0) {
		o->vt        = lbl_8028B0B0;
		lbl_8042C7D8 = 0;
		dtor_80136EA8(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
