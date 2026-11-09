// Copies the payload of the second block (from 0x4C) into the first, count times element size, and returns 1.

extern "C" {
void* memcpy(void*, const void*, unsigned);
struct Block8020C92C {
	unsigned char pad[0x24];
	int f24;
	unsigned char pad2[4];
	int f2c;
	unsigned char pad3[0x4c - 0x30];
	unsigned char d[1];
};

int fn_8020C92C(Block8020C92C* a, Block8020C92C* b)
{
	memcpy(a->d, b->d, a->f24 * a->f2c);
	return 1;
}
}
