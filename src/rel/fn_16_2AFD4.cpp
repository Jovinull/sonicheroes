typedef unsigned char u8;
typedef unsigned int u32;
extern "C" {
void* copyVec3(void*, void*);
void fn_16_900(void*, void*);

struct Inner {
	u8 pad[0x2C];
	u8* unk2C;
};
struct Obj {
	u8 pad0[0x28];
	char* unk28;
	u8 pad2C[0xB8 - 0x2C];
	u8 unkB8;
};

void fn_16_2AFD4(register Obj* obj)
{
	u8* p = ((Inner*)obj->unk28)->unk2C;
	copyVec3((char*)obj + 0xC8, copyVec3((char*)obj + 0xBC, obj->unk28));
	fn_16_900((char*)obj + 0xD4, obj->unk28 + 0xC);
	obj->unkB8 = *p;
}
}
