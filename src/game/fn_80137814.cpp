// Destructor: stores the class vtable at 0x18, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj80137814 {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char lbl_8028C388[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void __dt__7TObjectFv(void*, int);

Obj80137814* fn_80137814(Obj80137814* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8028C388;
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
