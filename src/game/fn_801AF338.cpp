// Copies a record's fields (0x14, 0x18, the bytes at 0x20 and 0x23) into another
// and clears its word at 0x04. Returns 1.

extern "C" {
struct Record801AF338 {
	int unk0;
	int unk4;
	unsigned char pad[0xC];
	int field14; // 0x14
	int field18; // 0x18
	unsigned char pad2[4];
	unsigned char byte20; // 0x20
	unsigned char pad3[2];
	unsigned char byte23; // 0x23
};

int fn_801AF338(Record801AF338* dst, Record801AF338* src)
{
	dst->field18 = src->field18;
	dst->field14 = src->field14;
	dst->byte20  = src->byte20;
	dst->byte23  = src->byte23;
	dst->unk4    = 0;
	return 1;
}
}
