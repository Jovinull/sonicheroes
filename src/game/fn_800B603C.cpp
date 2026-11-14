// Cleans up the effect state: resets the pending block at 0x970, refreshes the
// slots via fn_800B48B8 and releases the stored object through the renderer
// callback, then clears the 0x9A0/0x9A4 pair.

struct Obj800B603C {
	unsigned char pad0[0x970];
	int f970;
	signed char f974;
	signed char f975;
	unsigned char pad976[0x9a0 - 0x976];
	int f9a0;
	void* f9a4;
};

extern "C" {
void fn_800B48B8(Obj800B603C* o);
void fn_8020AD44();
void fn_8020ADCC(int a);
extern void** lbl_8042C9A4;

void fn_800B603C(Obj800B603C* o)
{
	if (o->f970 != 0) {
		fn_8020AD44();
		fn_8020ADCC(2);
		o->f974 = 0;
		o->f975 = 0;
		o->f970 = 0;
	}
	fn_800B48B8(o);
	if (o->f9a4 != 0) {
		if (o->f9a4 != 0) {
			((void (*)(void*))lbl_8042C9A4[0x138 / 4])(o->f9a4);
		}
		o->f9a4 = 0;
		o->f9a0 = 0;
	}
}
}
