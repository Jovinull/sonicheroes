// Destructor: installs the vtable lbl_80242884, destroys the TObject base and frees the object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void __dt__7TObjectFv(void*, int);
extern int lbl_8042C148;
extern unsigned char lbl_80242884[];
struct Obj8004E624 {
	unsigned char pad[0x18];
	void* vt;
};

void* dtor_8004E624(Obj8004E624* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_80242884;
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
