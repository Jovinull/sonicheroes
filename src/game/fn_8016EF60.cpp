// Returns lbl_803EC968 +0x3BC.

extern "C" {
struct Glob8016EF60 {
	unsigned char pad[0x234];
	int f234;
	unsigned char pad1[0x2b4 - 0x238];
	int f2b4;
	unsigned char pad2[0x3bc - 0x2b8];
	int f3bc;
	unsigned char pad3[0x8b0 - 0x3c0];
	int f8b0;
};
extern Glob8016EF60 lbl_803EC968;

int fn_8016EF60(void)
{
	return lbl_803EC968.f3bc;
}
}
