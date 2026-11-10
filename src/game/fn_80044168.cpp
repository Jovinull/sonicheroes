// Same as fn_800440B8 but with the second speed limit lbl_8042D1FC.
struct Pl80044168 {
	unsigned char pad0[0x6F0];
	short f6F0;
	unsigned char pad6F2[2];
	short f6F4;
	short f6F6;
	unsigned char pad6F8[0xC];
	unsigned char pad704[0x80];
	int f784;
	unsigned char pad788[0x38];
	float f7C0;
	float f7C4;
	float f7C8;
	unsigned char pad7CC[0x88];
	float f854;
};

extern "C" {
extern float lbl_8042D1BC;
extern float lbl_8042D1FC;
void fn_800EF23C();

void fn_80044168(Pl80044168* p)
{
	fn_800EF23C();
	p->f6F0 = 0x40;
	p->f6F6 = p->f6F6 | 0x500;
	p->f7C0 = lbl_8042D1FC;
	float z = lbl_8042D1BC;
	p->f7C4 = z;
	p->f7C8 = z;
}
}
