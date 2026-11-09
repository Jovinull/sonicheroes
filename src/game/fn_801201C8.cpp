// Destructor: installs the vtable lbl_80289BA8, forgets the global singleton lbl_8042C700 if it is this object, destroys the TObject base and frees the object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void __dt__7TObjectFv(void*, int);
extern int lbl_8042C148;
extern unsigned lbl_8042C700;
extern unsigned char lbl_80289BA8[];
struct Obj801201C8 {
	unsigned char pad[0x18];
	void* vt;
};

Obj801201C8* fn_801201C8(Obj801201C8* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_80289BA8;
		if (lbl_8042C700 == (unsigned)o) {
			lbl_8042C700 = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
