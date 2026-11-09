// Destructor: stores the class vtable at 0x18, clears this object's slot (byte 0x39) in lbl_80304268, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj800BEE6C {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x39 - 0x1c];
	unsigned char b39;
};
extern unsigned char lbl_80253D88[];
extern int lbl_80304268[];
extern void* lbl_8042C148;
void __dt__7TObjectFv(void*, int);
void Free__9THeapCtrlFPv(void*, void*);

Obj800BEE6C* fn_800BEE6C(Obj800BEE6C* o, short flags)
{
	if (o != 0) {
		o->vt                = lbl_80253D88;
		lbl_80304268[o->b39] = 0;
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
