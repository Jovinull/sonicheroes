// Destructor: installs the vtable lbl_8028B070, clears the flag lbl_8042C7D0 and the three-word record lbl_8028B064, runs dtor_80136EA8 and frees the object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void dtor_80136EA8(void*, int);
extern int lbl_8042C148;
extern int lbl_8042C7D0;
struct Rec8013718C {
	int a;
	int b;
	int c;
};
extern Rec8013718C lbl_8028B064;
extern unsigned char lbl_8028B070[];
struct Obj8013718C {
	unsigned char pad[0x18];
	void* vt;
};

Obj8013718C* fn_8013718C(Obj8013718C* o, short flags)
{
	if (o != 0) {
		o->vt          = lbl_8028B070;
		lbl_8042C7D0   = 0;
		lbl_8028B064.a = 0;
		lbl_8028B064.b = 0;
		lbl_8028B064.c = 0;
		dtor_80136EA8(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
