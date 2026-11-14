// Destructor of a hook object: installs its vtable lbl_80254358, unregisters lbl_8042C430 from the
// 64-entry table lbl_803042C8 when word 0x34 is 1 (clearing it), then runs the base part (vtable
// lbl_80254594: drops this object from the five per-channel tables, indexed by the signed byte at
// 0x28, and from the six current-object globals) and the TObject base, and frees the object when
// flags > 0. Returns the object.
struct Obj800C0080 {
	unsigned char pad0[0x18];
	void* vt;
	unsigned char pad1C[0x28 - 0x1C];
	signed char channel; // 0x28
	unsigned char pad29[0x34 - 0x29];
	int f34;
};

extern "C" {
extern unsigned char lbl_80254358[];
extern unsigned char lbl_80254594[];
extern unsigned int lbl_803042C8[0x40];
extern unsigned int lbl_8042C430;
extern Obj800C0080* lbl_803043D8[];
extern Obj800C0080* lbl_803043C8[];
extern Obj800C0080* lbl_803043E8[];
extern Obj800C0080* lbl_803043F8[];
extern Obj800C0080* lbl_80304408[];
extern Obj800C0080* lbl_8042C40C;
extern Obj800C0080* lbl_8042C400;
extern Obj800C0080* lbl_8042C414;
extern Obj800C0080* lbl_8042C41C;
extern Obj800C0080* lbl_8042C424;
extern Obj800C0080* lbl_8042C42C;
extern int lbl_8042C148;
void __dt__7TObjectFv(void* o, int flags);
void Free__9THeapCtrlFPv(int heap, void* p);

Obj800C0080* fn_800C0080(Obj800C0080* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_80254358;
		if (o->f34 == 1) {
			unsigned int id = lbl_8042C430;
			int i;
			for (i = 0; i < 0x40; i++) {
				unsigned int v = lbl_803042C8[i];
				if (v == id) {
					lbl_803042C8[i] = 0;
					break;
				}
			}
			o->f34 = 0;
		}
		if (o != 0) {
			int c;
			o->vt = lbl_80254594;
			c     = o->channel;
			if (lbl_803043D8[c] == o) {
				lbl_803043D8[c] = 0;
			}
			if (lbl_803043C8[c] == o) {
				lbl_803043C8[c] = 0;
			}
			if (lbl_803043E8[c] == o) {
				lbl_803043E8[c] = 0;
			}
			if (lbl_803043F8[c] == o) {
				lbl_803043F8[c] = 0;
			}
			if (lbl_80304408[c] == o) {
				lbl_80304408[c] = 0;
			}
			if (lbl_8042C40C == o) {
				lbl_8042C40C = 0;
			}
			if (lbl_8042C400 == o) {
				lbl_8042C400 = 0;
			}
			if (lbl_8042C414 == o) {
				lbl_8042C414 = 0;
			}
			if (lbl_8042C41C == o) {
				lbl_8042C41C = 0;
			}
			if (lbl_8042C424 == o) {
				lbl_8042C424 = 0;
			}
			if (lbl_8042C42C == o) {
				lbl_8042C42C = 0;
			}
			__dt__7TObjectFv(o, 0);
		}
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
