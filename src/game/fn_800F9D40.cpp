// Destructor: stores the class vtable at 0x18, releases the owned handle at 0x34 (fn_80150958) and clears it, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj800F9D40 {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x34 - 0x1c];
	unsigned f34;
};
extern unsigned char lbl_8025A1B0[];
extern void* lbl_8042C148;
void __dt__7TObjectFv(void*, int);
void Free__9THeapCtrlFPv(void*, void*);
void fn_80150958(unsigned);

Obj800F9D40* fn_800F9D40(Obj800F9D40* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8025A1B0;
		if (o->f34 != 0) {
			fn_80150958(o->f34);
			o->f34 = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
