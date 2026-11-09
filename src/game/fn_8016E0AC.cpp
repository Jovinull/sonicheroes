// Stores arg0 into lbl_803EC968 +0x8B0; returns 1.

extern "C" {
struct Glob8016E0AC {
	unsigned char pad[0x234];
	int f234;
	unsigned char pad1[0x2b4 - 0x238];
	int f2b4;
	unsigned char pad2[0x3bc - 0x2b8];
	int f3bc;
	unsigned char pad3[0x8b0 - 0x3c0];
	int f8b0;
};
extern Glob8016E0AC lbl_803EC968;

int fn_8016E0AC(int a)
{
	lbl_803EC968.f8b0 = a;
	return 1;
}
}
