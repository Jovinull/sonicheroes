// Returns the two low bits of byte 3 of record i (0x30-byte records) of the table at 0x10.
struct Record80020330 {
	unsigned char pad0[0x3];
	unsigned char f3;
	unsigned char pad4[0x2C];
};

struct Obj80020330 {
	unsigned char pad0[0x10];
	Record80020330* records; // 0x10
};

extern "C" {
int fn_80020330(Obj80020330* o, int i)
{
	return *((unsigned char*)o->records + i * 0x30 + 3) & 3;
}
}
