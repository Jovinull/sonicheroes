struct RpClump;
extern char* lbl_8042C1D0;
extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

struct Obj {
	char pad[0xE4];
	RpClump* clump;
};

extern "C" void fn_16_273B0(register Obj* self)
{
	if (self->clump != 0) {
		fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), self->clump);
		fn_80150958(self->clump);
		self->clump = 0;
	}
}
