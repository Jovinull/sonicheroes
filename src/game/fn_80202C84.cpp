// Initialises the 16 flag records at the start of a block (HYPOTHESIS: the block at 0x58 of an
// fn_802038AC object, whose role is UNKNOWN). Each 16-byte record holds a mask and three
// selector words. Returns the address 0x1E0 bytes into the block (purpose UNKNOWN).
#include "types.h"

struct Record80202C84 {
	u32 w[4];
};

struct Block80202C84 {
	Record80202C84 entries[16]; // 0x0
};

extern "C" {
void* fn_80202C84(Block80202C84* block)
{
	block->entries[0].w[0]  = 0x0;
	block->entries[0].w[1]  = 0x1;
	block->entries[0].w[2]  = 0x0;
	block->entries[0].w[3]  = 0x0;
	block->entries[1].w[0]  = 0x0;
	block->entries[1].w[1]  = 0x1;
	block->entries[1].w[2]  = 0x0;
	block->entries[1].w[3]  = 0x0;
	block->entries[2].w[0]  = 0x10;
	block->entries[2].w[1]  = 0x0;
	block->entries[2].w[2]  = 0x0;
	block->entries[2].w[3]  = 0x1;
	block->entries[3].w[0]  = 0x0;
	block->entries[3].w[1]  = 0x0;
	block->entries[3].w[2]  = 0x1;
	block->entries[3].w[3]  = 0x0;
	block->entries[4].w[0]  = 0x400;
	block->entries[4].w[1]  = 0x1;
	block->entries[4].w[2]  = 0x0;
	block->entries[4].w[3]  = 0x0;
	block->entries[5].w[0]  = 0x0;
	block->entries[5].w[1]  = 0x1;
	block->entries[5].w[2]  = 0x0;
	block->entries[5].w[3]  = 0x0;
	block->entries[6].w[0]  = 0x0;
	block->entries[6].w[1]  = 0x0;
	block->entries[6].w[2]  = 0x0;
	block->entries[6].w[3]  = 0x1;
	block->entries[7].w[0]  = 0xA00;
	block->entries[7].w[1]  = 0x0;
	block->entries[7].w[2]  = 0x1;
	block->entries[7].w[3]  = 0x0;
	block->entries[8].w[0]  = 0x20;
	block->entries[8].w[1]  = 0x1;
	block->entries[8].w[2]  = 0x0;
	block->entries[8].w[3]  = 0x0;
	block->entries[9].w[0]  = 0x0;
	block->entries[9].w[1]  = 0x0;
	block->entries[9].w[2]  = 0x0;
	block->entries[9].w[3]  = 0x1;
	block->entries[10].w[0] = 0x0;
	block->entries[10].w[1] = 0x0;
	block->entries[10].w[2] = 0x0;
	block->entries[10].w[3] = 0x1;
	block->entries[11].w[0] = 0x40;
	block->entries[11].w[1] = 0x0;
	block->entries[11].w[2] = 0x1;
	block->entries[11].w[3] = 0x0;
	block->entries[12].w[0] = 0x0;
	block->entries[12].w[1] = 0x1;
	block->entries[12].w[2] = 0x0;
	block->entries[12].w[3] = 0x0;
	block->entries[13].w[0] = 0x1100;
	block->entries[13].w[1] = 0x1;
	block->entries[13].w[2] = 0x0;
	block->entries[13].w[3] = 0x0;
	block->entries[14].w[0] = 0x80;
	block->entries[14].w[1] = 0x0;
	block->entries[14].w[2] = 0x0;
	block->entries[14].w[3] = 0x1;
	block->entries[15].w[0] = 0x0;
	block->entries[15].w[1] = 0x0;
	block->entries[15].w[2] = 0x1;
	block->entries[15].w[3] = 0x0;
	return (u8*)block + 0x1E0;
}
}
