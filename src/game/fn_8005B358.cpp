// Destructor of TObjSetGen, the object-set generator (constructor __ct__10TObjSetGenFP7TObject,
// vtable __vt__10TObjSetGen; the TObjSetObj sub-object at +0x28 has its table at vtable + 0x2C):
// while the set is loaded (lbl_8042C298, lbl_8042C278) it runs the release callback (+0x8) of each
// of the 0x200 generated objects (lbl_8042C280) whose live flag (lbl_802FF3A0) is set, stopping at
// the first empty slot; it deletes the 0x800 records' buffers (lbl_802D63A0, 0x40 bytes each,
// +0x30) with the record counter +0x830, frees lbl_8042C284 and +0xA34, clears lbl_8042C298, runs
// the TObjSetObj and TObject destructors and frees the object when the delete flag is positive.
// HYPOTHESIS: the field roles are UNKNOWN.
// The release loop is an inline: its counter and table offset then share the counter's initial 0
// as in the retail code.

struct Generated8005B358 {
	unsigned char pad0[0x8];
	void (*release)(Generated8005B358* self); // 0x8
};

struct Record8005B358 {
	unsigned char pad0[0x30];
	void* buffer; // 0x30
	unsigned char pad34[0x40 - 0x34];
};

struct Obj8005B358 {
	unsigned char pad0[0x18];
	void* vt; // 0x18
	unsigned char pad1C[0x28 - 0x1C];
	unsigned char setObj[0x4]; // 0x28 (TObjSetObj)
	void* setObjVt;            // 0x2C
	unsigned char pad30[0x830 - 0x30];
	int record; // 0x830
	unsigned char pad834[0xA34 - 0x834];
	void* buffer; // 0xA34
};

struct RwGlobals8005B358 {
	unsigned char pad0[0x138];
	void (*rwfree)(void* block); // 0x138
};

extern "C" {
extern unsigned char __vt__10TObjSetGen[];
extern void* lbl_8042C298;
extern void* lbl_8042C278;
extern Generated8005B358** lbl_8042C280;
extern void* lbl_8042C284;
extern signed char lbl_802FF3A0[0x200];
extern Record8005B358 lbl_802D63A0[0x800];
extern RwGlobals8005B358* lbl_8042C9A4;
extern void* lbl_8042C148;
void __dl__FPv(void* p);
void __dt__10TObjSetObjFv(void* setObj, int flags);
void __dt__7TObjectFv(void*, int);
void Free__9THeapCtrlFPv(void*, void*);

static inline void ReleaseGenerated()
{
	for (int i = 0; i < 0x200; i++) {
		if (lbl_802FF3A0[i] != 0) {
			Generated8005B358* g = lbl_8042C280[i];
			if (g == 0) {
				break;
			}
			if (g->release != 0) {
				g->release(g);
			}
		}
	}
}

Obj8005B358* fn_8005B358(Obj8005B358* o, short flags)
{
	if (o != 0) {
		o->vt       = __vt__10TObjSetGen;
		o->setObjVt = __vt__10TObjSetGen + 0x2C;
		if (lbl_8042C298 != 0 && lbl_8042C278 != 0) {
			ReleaseGenerated();
		}
		for (o->record = 0; o->record < 0x800; o->record++) {
			if (lbl_802D63A0[o->record].buffer != 0) {
				__dl__FPv(lbl_802D63A0[o->record].buffer);
				lbl_802D63A0[o->record].buffer = 0;
			}
		}
		if (lbl_8042C284 != 0) {
			lbl_8042C9A4->rwfree(lbl_8042C284);
			lbl_8042C284 = 0;
		}
		if (o->buffer != 0) {
			lbl_8042C9A4->rwfree(o->buffer);
			o->buffer = 0;
		}
		lbl_8042C298 = 0;
		__dt__10TObjSetObjFv(o->setObj, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
