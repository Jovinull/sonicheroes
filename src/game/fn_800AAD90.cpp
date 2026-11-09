// TObject-derived destructor: stores the class vtable at 0x18, runs the TObject destructor and frees the object when the delete flag is positive; returns the object.

extern "C" {
struct Obj800AAD90 {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char lbl_802532BC[];
extern void* lbl_8042C148;
void __dt__7TObjectFv(void*, int);
void Free__9THeapCtrlFPv(void*, void*);

Obj800AAD90* fn_800AAD90(Obj800AAD90* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_802532BC;
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
