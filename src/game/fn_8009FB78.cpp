// Destructor of a singleton-like object: stores the class vtable at 0x18, clears lbl_8042C31C when it points at this object, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj8009FB78 {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char lbl_8024FE2C[];
extern Obj8009FB78* lbl_8042C31C;
extern void* lbl_8042C148;
void __dt__7TObjectFv(void*, int);
void Free__9THeapCtrlFPv(void*, void*);

Obj8009FB78* fn_8009FB78(Obj8009FB78* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8024FE2C;
		if (lbl_8042C31C == o) {
			lbl_8042C31C = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
