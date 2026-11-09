// Destructor of a singleton-like object: stores the class vtable at 0x18, clears lbl_8042C314 when it points at this object, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj800A1960 {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char lbl_8024FE58[];
extern Obj800A1960* lbl_8042C314;
extern void* lbl_8042C148;
void __dt__7TObjectFv(void*, int);
void Free__9THeapCtrlFPv(void*, void*);

Obj800A1960* fn_800A1960(Obj800A1960* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8024FE58;
		if (lbl_8042C314 == o) {
			lbl_8042C314 = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
