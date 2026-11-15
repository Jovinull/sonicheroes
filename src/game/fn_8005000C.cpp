// Destructor: stores the class vtable at 0x18, clears lbl_8042C248, runs the TObjCamera destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj8005000C {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char __vt__16TObjCameraEditor[];
extern int lbl_8042C248;
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void __dt__10TObjCameraFv(void*, int);

Obj8005000C* fn_8005000C(Obj8005000C* o, short flags)
{
	if (o != 0) {
		o->vt        = __vt__16TObjCameraEditor;
		lbl_8042C248 = 0;
		__dt__10TObjCameraFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
