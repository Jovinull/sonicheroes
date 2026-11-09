// Sets a record's first parameter pair and byte (0x64, 0x68, 0x6C) and marks
// them in the record's flags (0x100), when both the owner and the record are
// there. fn_80190604 does the same for the second set.

extern "C" {
struct Record8019044C {
	unsigned char pad0[8];
	unsigned int flags; // 0x08
	unsigned char pad1[0x58];
	int param0;           // 0x64
	int param1;           // 0x68
	unsigned char param2; // 0x6C
};

void fn_8019044C(void* owner, Record8019044C* record, int a, int b, unsigned char c)
{
	if (owner == 0 || record == 0) {
		return;
	}
	record->param0 = a;
	record->param1 = b;
	record->param2 = c;
	record->flags |= 0x100;
}
}
