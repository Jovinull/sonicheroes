// When the block from fn_80159698 has bit 0x01000000 set at +8, runs fn_8015E4C8 with the object's +0x34 and the u16 at +4 of its +0x80 record; returns arg0.

extern "C" {
struct Flags8015E920 {
	unsigned char pad[8];
	unsigned f8;
};
struct Rec8015E920 {
	unsigned char pad[4];
	unsigned short f4;
};
struct Obj8015E920 {
	unsigned char pad[0x34];
	int f34;
	unsigned char pad1[0x80 - 0x38];
	Rec8015E920* f80;
};
void* fn_80159698(void*);
void fn_8015E4C8(void*, int, unsigned short);

void* fn_8015E920(void* a, Obj8015E920* o)
{
	if (((Flags8015E920*)fn_80159698(o))->f8 & 0x01000000) {
		fn_8015E4C8(a, o->f34, o->f80->f4);
	}
	return a;
}
}
