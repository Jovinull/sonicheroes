// Destructor: stores the class vtable at 0x18; if the handle at 0xE8 is held, notifies fn_8015BBF8 and releases it (fn_80150958); then destroys the embedded C_COLLI at 0x28, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj800F7A6C {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0xe8 - 0x1c];
	unsigned fe8;
};
struct Globals800F7A6C {
	unsigned char pad[0x72a0];
	int f72a0;
};
extern Globals800F7A6C* lbl_8042C1D0;
extern unsigned char lbl_8025A0A8[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void __dt__7TObjectFv(void*, int);
void __dt__7C_COLLIFv(void*, int);
void fn_80150958(unsigned);
void fn_8015BBF8(int, unsigned);

Obj800F7A6C* fn_800F7A6C(Obj800F7A6C* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8025A0A8;
		if (o->fe8 != 0) {
			fn_8015BBF8(lbl_8042C1D0->f72a0, o->fe8);
			fn_80150958(o->fe8);
			o->fe8 = 0;
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
