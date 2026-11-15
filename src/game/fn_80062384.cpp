// PARTICLE_TASK::~PARTICLE_TASK() (CORROBORATED by PS2 metadata): destroys both bases, PARTICLE_MATERIAL and
// TObject, as the only PS2 function referencing both destructors does.
// Names are from PS2; the symbol keeps its address-based name.

// Destructor: installs the class vtable at +0x18 and the sub-object vtable at +0x7C,
// frees the pointer at +0xAC through the engine free slot, destroys the
// PARTICLE_MATERIAL sub-object at +0x28 and the TObject base, and frees the
// object when flags > 0; returns the object.

extern "C" {
void Free__9THeapCtrlFPv(int, void*);
void __dt__17PARTICLE_MATERIALFv(void*, int);
void __dt__7TObjectFv(void*, int);
extern int lbl_8042C148;
extern unsigned char lbl_80243B38[];
extern void** lbl_8042C9A4;

struct Obj80062384 {
	unsigned char pad0[0x18];
	void* vt;
	unsigned char pad1[0x7c - 0x1c];
	void* vt2;
	unsigned char pad2[0xac - 0x80];
	void* fAC;
};

void* fn_80062384(Obj80062384* o, short flags)
{
	if (o != 0) {
		o->vt  = lbl_80243B38;
		o->vt2 = lbl_80243B38 + 0x2c;
		if (o->fAC != 0) {
			((void (*)(void*, void**))lbl_8042C9A4[0x138 / 4])(o->fAC, lbl_8042C9A4);
			o->fAC = 0;
		}
		__dt__17PARTICLE_MATERIALFv((unsigned char*)o + 0x28, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
