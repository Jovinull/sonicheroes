// Destructor: stores the class vtable at 0x18, clears this object's entry (signed byte 0x28) in lbl_803E7238 when it points back at it, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj80104184 {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x28 - 0x1c];
	signed char c28;
};
extern unsigned char lbl_8025AAB4[];
extern Obj80104184* lbl_803E7238[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void __dt__7TObjectFv(void*, int);

Obj80104184* fn_80104184(Obj80104184* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8025AAB4;
		if (lbl_803E7238[o->c28] == o) {
			lbl_803E7238[o->c28] = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
