// Destructor: installs the vtable lbl_8028936C, releases the handle at 0x11C (fn_8015BBF8 then fn_80150958), destroys the C_COLLI sub-object at +0x28 and the TObject base, and frees the object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void __dt__7C_COLLIFv(void*, int);
void __dt__7TObjectFv(void*, int);
void fn_80150958(unsigned);
void fn_8015BBF8(int, unsigned);
struct Glob8011A79C {
	unsigned char pad[0x7258];
	int f7258;
};
extern Glob8011A79C* lbl_8042C1D0;
extern int lbl_8042C148;
extern unsigned char lbl_8028936C[];
struct Obj8011A79C {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x11C - 0x1c];
	unsigned h;
};

Obj8011A79C* fn_8011A79C(Obj8011A79C* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8028936C;
		if (o->h != 0) {
			fn_8015BBF8(lbl_8042C1D0->f7258, o->h);
			fn_80150958(o->h);
			o->h = 0;
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
