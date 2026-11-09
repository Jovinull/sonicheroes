// Destructor: stores the class vtable at 0x18, clears lbl_8042C238, runs dtor_8004E624 and frees the object when the delete flag is positive.

extern "C" {
struct Obj8004FF40 {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char lbl_802428E0[];
extern int lbl_8042C238;
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void dtor_8004E624(void*, int);

Obj8004FF40* fn_8004FF40(Obj8004FF40* o, short flags)
{
	if (o != 0) {
		o->vt        = lbl_802428E0;
		lbl_8042C238 = 0;
		dtor_8004E624(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
