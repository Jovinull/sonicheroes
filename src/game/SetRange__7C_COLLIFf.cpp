// Stores the collision range at +0xC.

extern "C" {
struct Obj7C_COLLI_SetRange {
	unsigned char pad[0xc];
	float fc;
};

void SetRange__7C_COLLIFf(Obj7C_COLLI_SetRange* o, float f)
{
	o->fc = f;
}
}
