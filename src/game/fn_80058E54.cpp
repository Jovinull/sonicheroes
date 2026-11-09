// Destructor: stores the class vtable at 0x18 and the sub-object vtable at 0x2C, clears lbl_8042C278, runs fn_8005B358 and frees the object when the delete flag is positive.

extern "C" {
struct Obj80058E54 {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x2c - 0x1c];
	void* f2c;
};
extern unsigned char lbl_802430FC[];
extern int lbl_8042C278;
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void fn_8005B358(void*, int);

Obj80058E54* fn_80058E54(Obj80058E54* o, short flags)
{
	if (o != 0) {
		o->vt        = lbl_802430FC;
		o->f2c       = lbl_802430FC + 0x2c;
		lbl_8042C278 = 0;
		fn_8005B358(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
