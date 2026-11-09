// For each priority i below the count at 0x39, calls fn_8008DB48 on every slot (except the one at 0x3A) whose field 0x9B0 equals i.

extern "C" {
struct Slot80092D0C {
	unsigned char pad[0x9b0];
	int f9b0;
};
struct Obj80092D0C {
	unsigned char pad[0x39];
	signed char c39;
	signed char c3a;
	unsigned char pad1[0x114 - 0x3b];
	Slot80092D0C* slots[8];
};
void fn_8008DB48(Slot80092D0C*);

void fn_80092D0C(Obj80092D0C* o)
{
	int j;
	int i;
	for (i = 0; i < o->c39; i++) {
		for (j = 0; j < o->c39; j++) {
			if (j != o->c3a) {
				Slot80092D0C* t = o->slots[j];
				if (t != 0 && t->f9b0 == i) {
					fn_8008DB48(t);
				}
			}
		}
	}
}
}
