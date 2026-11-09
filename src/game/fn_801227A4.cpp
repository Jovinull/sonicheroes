// Destructor: installs the vtable lbl_80289D78, releases the handle at +0x64, destroys the TObject base and frees the object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void __dt__7TObjectFv(void*, int);
void fn_80150958(unsigned);
extern int lbl_8042C148;
extern unsigned char lbl_80289D78[];
struct Obj801227A4 {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x64 - 0x1c];
	unsigned f64;
};

Obj801227A4* fn_801227A4(Obj801227A4* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_80289D78;
		if (o->f64 != 0) {
			fn_80150958(o->f64);
			o->f64 = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
