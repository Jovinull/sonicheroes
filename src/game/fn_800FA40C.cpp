// Destructor: stores the class vtable at 0x18, releases the owned handle at 0x34 (fn_80150958) and clears it, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj800FA40C {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x34 - 0x1c];
	unsigned f;
};
extern unsigned char lbl_8025A1DC[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void __dt__7TObjectFv(void*, int);
void fn_80150958(unsigned);

Obj800FA40C* fn_800FA40C(Obj800FA40C* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8025A1DC;
		if (o->f != 0) {
			fn_80150958(o->f);
			o->f = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
