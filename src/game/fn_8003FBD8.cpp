// Resets the player's action state: caches two bytes of its reference block, clears the counters and writes the speed values into the physics record.
struct Ref8003FBD8 {
	unsigned char pad0[0x38];
	unsigned char f38;
	unsigned char pad1[0x113];
	unsigned char f14C;
};
struct Spd8003FBD8 {
	unsigned char pad0[0x14];
	float f14;
	float f18;
	float f1C;
};
struct Pl8003FBD8 {
	unsigned char pad0[0x38];
	Spd8003FBD8* volatile f38;
	unsigned char pad1[0x6B4];
	short f6F0;
	unsigned char pad2[0x2];
	short f6F4;
	unsigned char pad3[0x82];
	short f778;
	unsigned char pad4[0x11E];
	float f898;
	unsigned char pad5[0xC];
	float f8A8;
	unsigned char pad6[0x2];
	short f8AE;
	unsigned char pad7[0x108];
	Ref8003FBD8* volatile f9B8;
	signed char f9BC;
	unsigned char pad8[0x1];
	signed char f9BE;
};

extern "C" {
extern float lbl_8042D160;
extern float lbl_8042D164;

void fn_8003FBD8(Pl8003FBD8* p)
{
	p->f9BC     = (signed char)p->f9B8->f38;
	p->f9BE     = (signed char)p->f9B8->f14C;
	p->f6F4     = 0;
	p->f6F0     = 0;
	p->f778     = 0;
	p->f8AE     = 0;
	p->f38->f14 = p->f898;
	p->f38->f18 = p->f8A8;
	p->f38->f1C = lbl_8042D160 * (p->f898 * lbl_8042D164);
}
}
