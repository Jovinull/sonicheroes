// Destructor: installs the vtable lbl_8025A12C, releases the handle at 0xC0, marks the record at 0xDC (bit 0 of +4) and clears it, destroys the C_COLLI sub-object at +0x28 and the TObject base, and frees the object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void __dt__7C_COLLIFv(void*, int);
void __dt__7TObjectFv(void*, int);
void fn_80150958(unsigned);
extern int lbl_8042C148;
extern unsigned char lbl_8025A12C[];
struct Flags800F8BFC {
	unsigned char pad[4];
	unsigned short f4;
};
struct Obj800F8BFC {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0xc0 - 0x1c];
	unsigned fc0;
	unsigned char pad2[0xdc - 0xc4];
	Flags800F8BFC* fdc;
};

Obj800F8BFC* fn_800F8BFC(Obj800F8BFC* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8025A12C;
		if (o->fc0 != 0) {
			fn_80150958(o->fc0);
			o->fc0 = 0;
		}
		if (o->fdc != 0) {
			o->fdc->f4 = o->fdc->f4 | 1;
			o->fdc     = 0;
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
