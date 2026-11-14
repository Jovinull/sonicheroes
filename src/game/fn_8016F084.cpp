// Runs six reset routines in order (fn_8016F0C8, fn_80172F10, fn_8016DE10, fn_80169D60,
// fn_80171B54, fn_801765B8) and clears word 0x3BC of lbl_803EC968.
struct Obj8016F084 {
	unsigned char pad0[0x3BC];
	int f3BC;
};

extern "C" {
extern Obj8016F084 lbl_803EC968;
void fn_8016F0C8(void);
void fn_80172F10(void);
void fn_8016DE10(void);
void fn_80169D60(void);
void fn_80171B54(void);
void fn_801765B8(void);

void fn_8016F084(void)
{
	fn_8016F0C8();
	fn_80172F10();
	fn_8016DE10();
	fn_80169D60();
	fn_80171B54();
	fn_801765B8();
	lbl_803EC968.f3BC = 0;
}
}
