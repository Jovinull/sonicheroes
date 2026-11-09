// TObject-derived destructor: stores the class vtable at 0x18, runs the TObject destructor and frees the object when the delete flag is positive; returns the object.

extern "C" {
struct Obj8009E744 {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char lbl_8024FDB0[];
extern void* lbl_8042C148;
void __dt__7TObjectFv(void*, int);
void Free__9THeapCtrlFPv(void*, void*);

Obj8009E744* fn_8009E744(Obj8009E744* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8024FDB0;
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
