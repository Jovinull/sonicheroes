// Destructor of a hook object: installs its vtable lbl_8025422C, then runs the base part (vtable
// lbl_80254594: drops this object from the five per-channel tables, indexed by the signed byte at
// 0x28, and from the six current-object globals) and the TObject base, and frees the object when
// flags > 0. Returns the object.
struct Obj800BFB3C {
	unsigned char pad0[0x18];
	void* vt;
	unsigned char pad1C[0x28 - 0x1C];
	signed char channel; // 0x28
	unsigned char pad29[0x44 - 0x29];
	int f44;
};

extern "C" {
extern unsigned char lbl_8025422C[];
extern unsigned char lbl_80254594[];
extern Obj800BFB3C* lbl_803043D8[];
extern Obj800BFB3C* lbl_803043C8[];
extern Obj800BFB3C* lbl_803043E8[];
extern Obj800BFB3C* lbl_803043F8[];
extern Obj800BFB3C* lbl_80304408[];
extern Obj800BFB3C* lbl_8042C40C;
extern Obj800BFB3C* lbl_8042C400;
extern Obj800BFB3C* lbl_8042C414;
extern Obj800BFB3C* lbl_8042C41C;
extern Obj800BFB3C* lbl_8042C424;
extern Obj800BFB3C* lbl_8042C42C;
extern int lbl_8042C148;
void __dt__7TObjectFv(void* o, int flags);
void Free__9THeapCtrlFPv(int heap, void* p);

Obj800BFB3C* fn_800BFB3C(Obj800BFB3C* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8025422C;
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
