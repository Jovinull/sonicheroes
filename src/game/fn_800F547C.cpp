// Destructor: stores the class vtable at 0x18, releases the owned handle at 0xb4 (fn_80150958) and clears it, destroys the embedded C_COLLI at 0x28, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj800F547C {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0xb4 - 0x1c];
	unsigned f;
};
extern unsigned char lbl_80259DE8[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void __dt__7TObjectFv(void*, int);
void fn_80150958(unsigned);
void __dt__7C_COLLIFv(void*, int);

Obj800F547C* fn_800F547C(Obj800F547C* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_80259DE8;
		if (o->f != 0) {
			fn_80150958(o->f);
			o->f = 0;
		}
		__dt__7C_COLLIFv((unsigned char*)o + 0x28, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
