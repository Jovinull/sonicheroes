// Destructor: stores the class vtable at 0x18 and the sub-object vtable at 0x7C, runs fn_80062384 and frees the object when the delete flag is positive.

extern "C" {
struct Obj8011E528 {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x7c - 0x1c];
	void* f7c;
};
extern unsigned char lbl_80289564[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void fn_80062384(void*, int);

Obj8011E528* fn_8011E528(Obj8011E528* o, short flags)
{
	if (o != 0) {
		o->vt  = lbl_80289564;
		o->f7c = lbl_80289564 + 0x2c;
		fn_80062384(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
