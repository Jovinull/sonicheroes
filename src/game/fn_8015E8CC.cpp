// When the block from fn_80159698 has bit 0x01000000 set at +8, returns the value at +8 of the record at +0x34 minus 7 (0 if there is none); otherwise 0.

extern "C" {
struct Flags8015E8CC {
	unsigned char pad[8];
	unsigned f8;
};
struct Obj8015E8CC {
	unsigned char pad[0x34];
	Flags8015E8CC* f34;
};
void* fn_80159698(void*);

int fn_8015E8CC(Obj8015E8CC* o)
{
	if (((Flags8015E8CC*)fn_80159698(o))->f8 & 0x01000000) {
		Flags8015E8CC* t = o->f34;
		if (t != 0) {
			return t->f8 - 7;
		}
	}
	return 0;
}
}
