// Destructor: stores the class vtable at 0x18 and the sub-object vtable at 0x7C, runs fn_80062384 and frees the object when the delete flag is positive.

extern "C" {
struct Obj800A201C {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x7c - 0x1c];
	void* f7c;
};
extern unsigned char lbl_8024FDDC[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void fn_80062384(void*, int);

Obj800A201C* fn_800A201C(Obj800A201C* o, short flags)
{
	if (o != 0) {
		o->vt  = lbl_8024FDDC;
		o->f7c = lbl_8024FDDC + 0x2c;
		fn_80062384(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
