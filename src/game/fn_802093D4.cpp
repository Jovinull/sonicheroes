// Derives the per-channel loop end offsets from the start offsets once the object is active.
struct Obj802093D4 {
	unsigned int f0;
	unsigned char pad4[188];
	int fC0;
	unsigned char padC4[12];
	int fD0;
	unsigned char padD4[52];
	int f108;
	unsigned char pad10C[12];
	int f118;
	unsigned char pad11C[52];
	int f150;
	unsigned char pad154[12];
	int f160;
	unsigned char pad164[52];
	int f198;
	unsigned char pad19C[12];
	int f1A8;
	unsigned char pad1AC[52];
	int f1E0;
	unsigned char pad1E4[12];
	int f1F0;
	unsigned char pad1F4[52];
	int f228;
	unsigned char pad22C[12];
	int f238;
	unsigned char pad23C[52];
	int f270;
	unsigned char pad274[12];
	int f280;
	unsigned char pad284[52];
	int f2B8;
	unsigned char pad2BC[12];
	int f2C8;
	unsigned char pad2CC[52];
	int f300;
	unsigned char pad304[12];
	int f310;
	unsigned char pad314[52];
	int f348;
	unsigned char pad34C[12];
	int f358;
	unsigned char pad35C[52];
	int f390;
	unsigned char pad394[12];
	int f3A0;
	unsigned char pad3A4[52];
	int f3D8;
	unsigned char pad3DC[12];
	int f3E8;
	unsigned char pad3EC[52];
	int f420;
	unsigned char pad424[12];
	int f430;
	unsigned char pad434[52];
	int f468;
	unsigned char pad46C[12];
	int f478;
	unsigned char pad47C[52];
	int f4B0;
	unsigned char pad4B4[12];
	int f4C0;
	unsigned char pad4C4[52];
	int f4F8;
	unsigned char pad4FC[12];
	int f508;
};

extern "C" {
void fn_802093D4(Obj802093D4* o)
{
	if (o->f0 & 0x80000000) {
		o->fD0  = o->fC0 - 0x2000;
		o->f118 = o->f108 - 0x2000;
		o->f160 = o->f150 - 0x2000;
		o->f1A8 = o->f198 - 0x2000;
		o->f1F0 = o->f1E0 - 0x2000;
		o->f238 = o->f228 - 0x2000;
		o->f280 = o->f270 - 0x2000;
		o->f2C8 = o->f2B8 - 0x2000;
		o->f310 = o->f300 - 0x2000;
		o->f358 = o->f348 - 0x2000;
		o->f3A0 = o->f390 - 0x2000;
		o->f3E8 = o->f3D8 - 0x2000;
		o->f430 = o->f420 - 0x2000;
		o->f478 = o->f468 - 0x2000;
		o->f4C0 = o->f4B0 - 0x2000;
		o->f508 = o->f4F8 - 0x2000;
	}
}
}
