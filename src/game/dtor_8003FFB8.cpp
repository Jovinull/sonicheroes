// Destructor: installs the vtable lbl_80241C20, destroys the two members at +0x91C / +0x8AC (guarded by the +0x760 sub-object), the C_COLLI sub-object at +0x28 and the TObject base, and frees the object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void __dt__7C_COLLIFv(void*, int);
void __dt__7TObjectFv(void*, int);
void dtor_800F1618(void*, int);
extern int lbl_8042C148;
extern unsigned char lbl_80241C20[];
struct Obj8003FFB8 {
	unsigned char pad[0x18];
	void* vt;
};

void* dtor_8003FFB8(Obj8003FFB8* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_80241C20;
		if ((unsigned char*)o + 0x760 != 0) {
			dtor_800F1618((unsigned char*)o + 0x91c, -1);
			dtor_800F1618((unsigned char*)o + 0x8ac, -1);
		}
		__dt__7C_COLLIFv((unsigned char*)o + 0x28, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
