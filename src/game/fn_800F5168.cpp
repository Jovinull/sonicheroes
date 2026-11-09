// Destructor: stores the class vtable at 0x18, releases the owned handle at 0x2c (fn_80150958) and clears it, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj800F5168 {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x2c - 0x1c];
	unsigned f2c;
};
extern unsigned char lbl_80259DBC[];
extern void* lbl_8042C148;
void __dt__7TObjectFv(void*, int);
void Free__9THeapCtrlFPv(void*, void*);
void fn_80150958(unsigned);

Obj800F5168* fn_800F5168(Obj800F5168* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_80259DBC;
		if (o->f2c != 0) {
			fn_80150958(o->f2c);
			o->f2c = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
