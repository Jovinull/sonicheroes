// Destructor: stores the class vtable at 0x18, clears lbl_8042C248, runs dtor_8004E624 and frees the object when the delete flag is positive.

extern "C" {
struct Obj8005000C {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char lbl_8024298C[];
extern int lbl_8042C248;
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void dtor_8004E624(void*, int);

Obj8005000C* fn_8005000C(Obj8005000C* o, short flags)
{
	if (o != 0) {
		o->vt        = lbl_8024298C;
		lbl_8042C248 = 0;
		dtor_8004E624(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
