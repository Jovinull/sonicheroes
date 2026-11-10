// Ors the flags into the entity's flag word at +0x90 and picks the float at +0x3C from the highest-priority flag (8, 4, 0x10, 0x20000, else default).
struct Ent800E67CC {
	unsigned char pad0[0x3C];
	float f3C;
	unsigned char pad40[0x50];
	unsigned int f90;
};

extern "C" {
extern float lbl_8042E250;
extern float lbl_8042E25C;
extern float lbl_8042E26C;
extern float lbl_8042E294;
extern float lbl_8042E2C0;

void fn_800E67CC(int a, int b, Ent800E67CC* e, unsigned int flags)
{
	e->f90 |= flags;
	if ((flags & 8) != 0) {
		e->f3C = lbl_8042E2C0;
		return;
	}
	if ((flags & 4) != 0) {
		e->f3C = lbl_8042E294;
		return;
	}
	if ((flags & 0x10) != 0) {
		e->f3C = lbl_8042E25C;
		return;
	}
	if ((flags & 0x20000) != 0) {
		e->f3C = lbl_8042E26C;
		return;
	}
	e->f3C = lbl_8042E250;
}
}
