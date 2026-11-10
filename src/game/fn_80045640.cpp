// Returns 1 when the player is allowed to use the action: in state 0xB, in one of the listed modes (mode 0x29 additionally needs to be the current member of its group) and with a live entry in the collision list.
struct Ref80045640 {
	unsigned char pad0[4];
	unsigned int f4;
};
struct Group80045640 {
	unsigned char pad0[0x3B];
	signed char f3B;
	unsigned char pad3C[0xD8];
	void* f114[1];
};
struct Obj80045640 {
	unsigned char pad0[0x28];
	unsigned char pad28[0x6C8];
	short f6F0;
	unsigned char pad6F2[0x6F];
	signed char f761;
	unsigned char pad762[0x256];
	Group80045640* f9B8;
};

extern "C" {
int fn_80089204();
Ref80045640* fn_80020BD8(void* p, int id);

int fn_80045640(Obj80045640* o)
{
	Ref80045640* r;
	unsigned int v;
	if (fn_80089204() == 0) {
		return 0;
	}
	if (o->f761 != 0xB) {
		return 0;
	}
	switch (o->f6F0) {
		case 0:
		case 0xC:
		case 0xD:
		case 0xE:
		case 0x23:
			break;
		case 0x29:
			if (o->f9B8->f114[o->f9B8->f3B] != o) {
				goto fail;
			}
			break;
		default:
		fail:
			return 0;
	}
	r = fn_80020BD8((char*)o + 0x28, 0x1D);
	if (r != 0) {
		v = r->f4;
	} else {
		v = 0;
	}
	if (v != 0) {
		return 1;
	}
	return 0;
}
}
