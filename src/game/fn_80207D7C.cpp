// Counts the 0x40-byte records of sound `index` in bank `bank` (see game/audio_system.h) whose
// byte range [0x08, 0x09] contains key. Bank words pack a count in the top byte and an offset
// from the bank start in the low 24 bits: the word at 0x08 indexes the sound table, each sound
// word a list of 16-byte groups, and each group word its records. Returns 0 for an empty bank or
// an index past the table.
// NonMatching: 2 word diffs. Retail forms the sound-table address as data + offset into r4 and
// then indexes it (add r4,r7,r6; lwzx r4,r4,r0); MWCC adds offset and index*4 first. Address
// spellings, index signedness and statement order did not change that.
#include "game/audio_system.h"

extern "C" {
int fn_80207D7C(int bank, unsigned int index, int key)
{
	unsigned char* data = lbl_8042CF6C->banks[bank].data;
	int n               = 0;
	unsigned int table;
	unsigned int sound;
	unsigned char* group;
	int groups;
	int i;
	if (data != 0) {
		table = *(unsigned int*)(data + 8);
		if ((table >> 24) > index) {
			sound  = ((unsigned int*)(data + (table & 0xFFFFFF)))[index];
			groups = sound >> 24;
			group  = data + (sound & 0xFFFFFF);
			for (i = 0; i < groups; i++) {
				unsigned char* rec = data + (*(unsigned int*)group & 0xFFFFFF);
				int count          = *(unsigned int*)group >> 24;
				int j;
				for (j = 0; j < count; j++) {
					if (rec[8] <= key && key <= rec[9]) {
						n++;
					}
					rec += 0x40;
				}
				group += 0x10;
			}
		}
	}
	return n;
}
}
