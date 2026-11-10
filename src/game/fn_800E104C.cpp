// Stores the vector in entity idx's record at +0x60, mirrors it into the entity's position vector and forwards both to fn_8003E9B4.
struct Ent800E104C {
	unsigned char pad0[0x60];
	float f60;
	float f64;
	float f68;
};
struct V3_800E104C {
	float x;
	float y;
	float z;
};

extern "C" {
extern int lbl_802AD090[];
extern V3_800E104C* lbl_802AD0B0[];
extern Ent800E104C* lbl_802AD0D0[];
void fn_8003E9B4(int a, V3_800E104C* b, Ent800E104C* c);

void fn_800E104C(int idx, float x, float y, float z)
{
	int a          = lbl_802AD090[idx];
	V3_800E104C* v = lbl_802AD0B0[idx];
	Ent800E104C* e = lbl_802AD0D0[idx];
	e->f60         = x;
	e->f64         = y;
	e->f68         = z;
	v->x           = e->f60;
	v->y           = e->f64;
	v->z           = e->f68;
	fn_8003E9B4(a, v, e);
}
}
