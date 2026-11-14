// For every 0x40-byte record of sound `index` in bank `bank` (see game/audio_system.h and
// fn_80207D7C for the bank layout) whose byte range [0x08, 0x09] contains key, takes the next node
// of `list` (fn_80206328) and, when it carries data, starts it with fn_80207E1C. The table at bank
// word 0x04 is passed along.
// NonMatching: same 73 instructions, 43 word diffs. Saved registers are colored differently
// (retail: rec r31, group r30, node r29, data r28, table4 r27, params r19-r22) and, as in
// fn_80207D7C, retail adds the sound-table offset to data before indexing it. Declaration order
// does not change either. Compiled with -use_lmw_stmw on (retail saves r19-r31 with stmw).
#include "game/audio_system.h"

extern "C" {
PoolListNode* fn_80206328(PoolListNode** list, PoolListNode* prev);
void fn_80207E1C(int bank, void* voice, unsigned char* group, unsigned char* data,
    unsigned char* record, int key, unsigned char* table4, int param);

void fn_80207C58(PoolListNode** list, int bank, unsigned int index, int key, int param)
{
	PoolListNode* node  = 0;
	unsigned char* data = lbl_8042CF6C->banks[bank].data;
	unsigned int table;
	unsigned int sound;
	unsigned char* table4;
	unsigned char* group;
	int groups;
	int i;
	if (data != 0) {
		table = *(unsigned int*)(data + 8);
		if ((table >> 24) > index) {
			sound  = ((unsigned int*)(data + (table & 0xFFFFFF)))[index];
			table4 = data + (*(unsigned int*)(data + 4) & 0xFFFFFF);
			groups = sound >> 24;
			group  = data + (sound & 0xFFFFFF);
			for (i = 0; i < groups; i++) {
				unsigned int w     = *(unsigned int*)group;
				int count          = w >> 24;
				unsigned char* rec = data + (w & 0xFFFFFF);
				int j;
				for (j = 0; j < count; j++) {
					if (rec[8] <= key && key <= rec[9]) {
						PoolListNode* next = fn_80206328(list, node);
						node               = next;
						if (next != 0 && next->data != 0) {
							fn_80207E1C(bank, next->data, group, data, rec, key, table4, param);
						}
					}
					rec += 0x40;
				}
				group += 0x10;
			}
		}
	}
}
}
