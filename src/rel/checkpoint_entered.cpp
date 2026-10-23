#include "types.h"

// TObjCheckpoint::CheckPlayerNumberEntered (the PS2 build's name;
// checkpointCheckPlayerNumberEntered here): whether the player number is the
// one kept at 0x30.

typedef struct Checkpoint {
	u8 unk00[0x30];
	s8 player; // 0x30
} Checkpoint;

extern "C" bool checkpointCheckPlayerNumberEntered(Checkpoint* object, s32 no)
{
	return object->player == no;
}
