// Resets the rotation order of the player slots: the current one (byte 0x3A) gets rank 0 and the others get ranks 1..n-1 counted from it (n = byte 0x39).

extern "C" {
struct Slot80092C00 {
	unsigned char pad[0x9b0];
	int f9b0;
};
struct Obj80092C00 {
	unsigned char pad[0x39];
	signed char c39;
	signed char c3a;
	unsigned char pad1[0x114 - 0x3b];
	Slot80092C00* q[8];
};

void fn_80092C00(Obj80092C00* o)
{
	int v;
	o->q[o->c3a]->f9b0 = 0;
	for (v = 1; v < o->c39; v++) {
		o->q[(o->c3a + v) % o->c39]->f9b0 = v;
	}
}
}
