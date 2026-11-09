// Destructor: installs the vtable lbl_8028AFE8, clears the seven-word record lbl_8028AFA0 and the flag lbl_8042C7C8, runs dtor_80136EA8 and frees the object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void dtor_80136EA8(void*, int);
extern int lbl_8042C148;
extern int lbl_8042C7C8;
struct Rec801369EC {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	int g;
};
extern Rec801369EC lbl_8028AFA0;
extern unsigned char lbl_8028AFE8[];
struct Obj801369EC {
	unsigned char pad[0x18];
	void* vt;
};

Obj801369EC* fn_801369EC(Obj801369EC* o, short flags)
{
	if (o != 0) {
		o->vt          = lbl_8028AFE8;
		lbl_8028AFA0.a = 0;
		lbl_8028AFA0.b = 0;
		lbl_8028AFA0.c = 0;
		lbl_8028AFA0.d = 0;
		lbl_8028AFA0.e = 0;
		lbl_8028AFA0.f = 0;
		lbl_8028AFA0.g = 0;
		lbl_8042C7C8   = 0;
		dtor_80136EA8(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
