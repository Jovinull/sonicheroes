struct Fighter80044844 {
	unsigned char pad0[0x639];
	unsigned char f639;
	short f63A;
	short f63C;
	int f640;
	unsigned char pad1[0x6F0 - 0x644];
	short f6F0;
	unsigned char pad2[0x6F4 - 0x6F2];
	short f6F4;
	short f6F6;
	unsigned char pad3[0x8AE - 0x6F8];
	short f8AE;
};

extern "C" {
void fn_8008A2D4(void* p);

void fn_80044844(Fighter80044844* f)
{
	f->f6F6 = f->f6F6 & ~0x500;
	f->f63A = 0;
	f->f63C = 0;
	f->f640 = 0;
	f->f639 = 0;
	f->f6F0 = 0x1B;
	f->f8AE = 0x37;
	fn_8008A2D4(f);
}
}
