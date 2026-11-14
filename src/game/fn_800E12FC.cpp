// Sets the three floats at 0x60 of b and the three floats at 0x00 of a to lbl_8042E1F0, skipping
// a null pointer.
struct Vec800E12FC {
	float x;
	float y;
	float z;
};

struct Obj800E12FC {
	unsigned char pad0[0x60];
	Vec800E12FC v60;
};

extern "C" {
extern const float lbl_8042E1F0;

void fn_800E12FC(Vec800E12FC* a, Obj800E12FC* b)
{
	if (b != 0) {
		b->v60.x = b->v60.y = b->v60.z = lbl_8042E1F0;
	}
	if (a != 0) {
		a->x = a->y = a->z = lbl_8042E1F0;
	}
}
}
