// Enters the 0x40 action: runs the common start, sets its flags and speed limits (lbl_8042D1F8, lbl_8042D1BC).
struct Pl800440B8 {
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
extern float lbl_8042D1F8;
void fn_800EF23C();

void fn_800440B8(Pl800440B8* p)
{
	fn_800EF23C();
	p->f6F0 = 0x40;
	p->f6F6 = p->f6F6 | 0x500;
	p->f7C0 = lbl_8042D1F8;
	float z = lbl_8042D1BC;
	p->f7C4 = z;
	p->f7C8 = z;
}
}
