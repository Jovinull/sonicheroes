// Destructor: installs the vtable lbl_8028B024, destroys the TObject base and frees the object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void __dt__7TObjectFv(void*, int);
extern int lbl_8042C148;
extern unsigned char lbl_8028B024[];
struct Obj80136EA8 {
	unsigned char pad[0x18];
	void* vt;
};

void* dtor_80136EA8(Obj80136EA8* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8028B024;
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
