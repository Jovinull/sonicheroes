#include "types.h"

// Takes the next 16-byte entry of a queue (HYPOTHESIS; the queue's type and the meaning of its
// entries are UNKNOWN): NULL when the queue holds nothing, otherwise the entry at the read index,
// which advances; once it reaches the count, both are reset so the queue is empty again. The
// 0x400-byte entry area gives room for 64 entries (inferred from the offsets).

struct Entry80203774 {
	u8 data[0x10];
};

struct Queue80203774 {
	Entry80203774 entries[0x40]; // 0x000
	s32 read;                    // 0x400
	s32 count;                   // 0x404
};

extern "C" Entry80203774* fn_80203774(Queue80203774* q)
{
	if (q->count == 0) {
		return NULL;
	}
	Entry80203774* entry = &q->entries[q->read];
	q->read++;
	if (q->read >= q->count) {
		q->read  = 0;
		q->count = 0;
	}
	return entry;
}
