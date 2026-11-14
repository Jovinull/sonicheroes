// Frame sync: when bit 2 of the flag byte 0x03 is set, copies the 0x40-byte matrix at 0x10 to
// 0x50; then passes the flags to fn_801A2F60 with the pointer at 0x98 and clears bits 0 and 2.
struct Matrix801A3178 {
	unsigned int w[16];
};

struct Frame801A3178 {
	unsigned char pad0[0x3];
	unsigned char flags; // 0x03
	unsigned char pad4[0xC];
	Matrix801A3178 local; // 0x10
	Matrix801A3178 world; // 0x50
	unsigned char pad90[0x8];
	void* f98;
};

extern "C" {
void fn_801A2F60(void* p, unsigned char flags);

void fn_801A3178(Frame801A3178* f)
{
	unsigned char flags = f->flags;
	if (flags & 4) {
		f->world = f->local;
	}
	fn_801A2F60(f->f98, flags);
	f->flags = flags & ~5;
}
}
