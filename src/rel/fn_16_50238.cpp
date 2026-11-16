typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;

struct Sub {
	u8 unk0[0x10];
	u8* table;
}; /* table at 0x10 */
struct Obj {
	u8 unk0[0xC];
	Sub* sub;
}; /* sub at 0xC */
struct Block {
	s32 count;
	u8* data;
	u8 unk8[0x14];
}; /* header 0x1C */

extern "C" {
s32 fn_8023506C(void* table, u32 type);
void* memcpy(void* dst, const void* src, u32 n);

Obj* fn_16_50238(void* unused, Obj* src, Obj* dst)
{
	Block* sb = 0;
	Block* db = 0;
	Obj* ret  = dst;
	s32 si;
	s32 di;
	s32 size;

	si = fn_8023506C(src->sub->table, 0x01000004);
	di = fn_8023506C(ret->sub->table, 0x01000004);
	if (si >= 0 && di >= 0) {
		sb   = (Block*)((u8*)src + si);
		db   = (Block*)((u8*)ret + di);
		size = sb->count * 0x28 + 0x1C;
		memcpy(db, sb, size);
		db->data = (u8*)db + 0x1C;
	}
	return ret;
}
}
