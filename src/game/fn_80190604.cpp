// Sets a record's second parameter pair and byte (0x70, 0x74, 0x78) and marks
// them in the record's flags (0x80), when both the owner and the record are
// there. fn_8019044C does the same for the first set.

extern "C" {
struct Record80190604 {
	unsigned char pad0[8];
	unsigned int flags; // 0x08
	unsigned char pad1[0x64];
	int param0;           // 0x70
	int param1;           // 0x74
	unsigned char param2; // 0x78
};

void fn_80190604(void* owner, Record80190604* record, int a, int b, unsigned char c)
{
	if (owner == 0 || record == 0) {
		return;
	}
	record->param0 = a;
	record->param1 = b;
	record->param2 = c;
	record->flags |= 0x80;
}
}
