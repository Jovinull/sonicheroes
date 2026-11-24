struct Obj {
	char pad[0xF8];
	void* clump;
};
struct World {
	char pad[0x725C];
	void* slot;
};
extern World* lbl_8042C1D0;
extern "C" void fn_8015BBF8(void* world, void* clump);
extern "C" void fn_80150958(void* clump);

extern "C" void fn_16_1C2F4(register Obj* obj)
{
	if (obj->clump != 0) {
		fn_8015BBF8(lbl_8042C1D0->slot, obj->clump);
		fn_80150958(obj->clump);
		obj->clump = 0;
	}
}
