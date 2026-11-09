// Copies the reactor's direction vector (+0x20..0x28) into *v.

extern "C" {
struct Reactor11CCL_REACTOR {
	unsigned char pad[0x20];
	float f20;
	float f24;
	float f28;
};
struct Vec11CCL_REACTOR {
	float x;
	float y;
	float z;
};

void GetDirection__11CCL_REACTORFP5RwV3d(Reactor11CCL_REACTOR* o, Vec11CCL_REACTOR* v)
{
	v->x = o->f20;
	v->y = o->f24;
	v->z = o->f28;
}
}
