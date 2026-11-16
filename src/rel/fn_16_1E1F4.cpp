typedef unsigned int u32;
struct Obj {
	char pad[0xD8];
	void* clump;
};
struct Game {
	char pad[0x725C];
	void* world;
};
extern "C" void fn_8015BBF8(void* world, void* clump);
extern "C" void fn_80150958(void* clump);
extern Game* lbl_8042C1D0;

extern "C" void fn_16_1E1F4(register Obj* obj)
{
	if (obj->clump != 0) {
		fn_8015BBF8(lbl_8042C1D0->world, obj->clump);
		fn_80150958(obj->clump);
		obj->clump = 0;
	}
}
