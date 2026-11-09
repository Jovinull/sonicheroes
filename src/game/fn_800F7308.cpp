// Initializes the object (fn_800F7B10): vtable-like pointer, word 0 from lbl_8042B6FC, id 0x124, byte 0xF9 = 3 and halfword 0x2C = 3; returns it.

extern "C" {
struct Obj800F7308 {
	int f0;
	unsigned char pad[0x14];
	void* f18;
	unsigned char pad1[2];
	short s1e;
	unsigned char pad2[0x2c - 0x20];
	short s2c;
	unsigned char pad3[0xf9 - 0x2e];
	unsigned char cf9;
};
extern unsigned char lbl_80259FD0[];
extern int lbl_8042B6FC;
void fn_800F7B10();

Obj800F7308* fn_800F7308(Obj800F7308* o)
{
	fn_800F7B10();
	o->f18 = lbl_80259FD0;
	o->f0  = lbl_8042B6FC;
	o->s1e = 0x124;
	o->cf9 = 3;
	o->s2c = 3;
	return o;
}
}
