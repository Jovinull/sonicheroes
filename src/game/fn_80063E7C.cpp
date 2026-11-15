// Destructor of a particle resource set (vtable lbl_80243BEC at +0x38): frees each buffer it owns
// (RwFree) by its ownership flag in +0x8: +0x18 (0x1000), +0x1C (0x2000), +0x20 (0x4000), +0x24
// (0x8000), +0x14 (0x10000), +0x28 (0x20000), +0x2C (0x40000, tested with +0x28 as the retail code
// does) and +0x30 (0x80000), then +0x0 and +0x4 unconditionally when set, and deletes the object
// (global operator delete) when the delete flag is positive. HYPOTHESIS: the buffer roles are
// UNKNOWN (see fn_80065930 and the PARTICLE_MATERIAL units).

struct RwGlobals80063E7C {
	unsigned char pad0[0x138];
	void (*rwfree)(void* block); // 0x138
};

struct Obj80063E7C {
	void* buffer0; // 0x0
	void* buffer4; // 0x4
	int owned;     // 0x8
	unsigned char padC[0x14 - 0xC];
	void* buffer14; // 0x14
	void* buffer18; // 0x18
	void* buffer1C; // 0x1C
	void* buffer20; // 0x20
	void* buffer24; // 0x24
	void* buffer28; // 0x28
	void* buffer2C; // 0x2C
	void* buffer30; // 0x30
	unsigned char pad34[0x38 - 0x34];
	void* vt; // 0x38
};

extern "C" {
extern unsigned char lbl_80243BEC[];
extern RwGlobals80063E7C* lbl_8042C9A4;
void __dl__FPv(void* p);

Obj80063E7C* fn_80063E7C(Obj80063E7C* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_80243BEC;
		if (o->buffer18 != 0 && (o->owned & 0x1000)) {
			lbl_8042C9A4->rwfree(o->buffer18);
		}
		if (o->buffer1C != 0 && (o->owned & 0x2000)) {
			lbl_8042C9A4->rwfree(o->buffer1C);
		}
		if (o->buffer20 != 0 && (o->owned & 0x4000)) {
			lbl_8042C9A4->rwfree(o->buffer20);
		}
		if (o->buffer24 != 0 && (o->owned & 0x8000)) {
			lbl_8042C9A4->rwfree(o->buffer24);
		}
		if (o->buffer14 != 0 && (o->owned & 0x10000)) {
			lbl_8042C9A4->rwfree(o->buffer14);
		}
		if (o->buffer28 != 0 && (o->owned & 0x20000)) {
			lbl_8042C9A4->rwfree(o->buffer28);
		}
		if (o->buffer28 != 0 && (o->owned & 0x40000)) {
			lbl_8042C9A4->rwfree(o->buffer2C);
		}
		if (o->buffer30 != 0 && (o->owned & 0x80000)) {
			lbl_8042C9A4->rwfree(o->buffer30);
		}
		if (o->buffer0 != 0) {
			lbl_8042C9A4->rwfree(o->buffer0);
		}
		if (o->buffer4 != 0) {
			lbl_8042C9A4->rwfree(o->buffer4);
		}
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
