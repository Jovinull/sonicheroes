#include "types.h"

class TQuestSeqCtrl
{
public:
	static s32 CheckSequenceVars(s32 flag);
	static void SetSequenceVars(s32 flag);

private:
	static u8 seqVars[128];
};

u8 TQuestSeqCtrl::seqVars[128];

s32 TQuestSeqCtrl::CheckSequenceVars(s32 flag)
{
	s32 byte;
	s32 bit;

	if (flag < 0 || flag > 1023) {
		return -1;
	}

	byte = (flag + 1) / 8;
	bit  = (flag + 1) % 8;
	if (bit > 0) {
		return (seqVars[byte] & (1 << (8 - bit))) >> (8 - bit);
	}
	return seqVars[byte - 1] & 1;
}

void TQuestSeqCtrl::SetSequenceVars(s32 flag)
{
	s32 byte;
	s32 bit;

	if (flag < 0 || flag > 1023) {
		return;
	}

	byte = (flag + 1) / 8;
	bit  = (flag + 1) % 8;
	if (bit > 0) {
		seqVars[byte] |= 1 << (8 - bit);
	} else {
		seqVars[byte - 1] |= 1;
	}
}
