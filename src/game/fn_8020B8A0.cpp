// Starts sequence `song` of sequence bank `bank` on a running audio pool slot (see
// game/audio_system.h). The bank starts with a zero-terminated table of words packing the song
// number (top byte) and the offset of its "gcaxMSBM" chunk. The slot's objects are released and
// its sequence state is cleared and restarted at the current time. Returns 0, or -1 when the slot
// is idle, the bank is empty, the song is missing or its chunk tag is wrong.
#include "game/audio_system.h"

struct SongHeader8020B8A0 {
	unsigned int tag0; // "gcax"
	unsigned int tag1; // "MSBM"
	unsigned char pad8[0x8];
	unsigned short f10;
	unsigned char pad12[0x1E - 0x12];
	unsigned short f1E;
	unsigned char pad20[0x28 - 0x20];
};

extern "C" {
extern const float lbl_804300D0;
void* memset(void* dst, int value, unsigned long n);
void fn_80206834(PoolListNode** list);

int fn_8020B8A0(PoolSlot* s, int bank, unsigned int song, int param)
{
	unsigned int* songs;
	unsigned int* entry;
	BOOL enabled;
	SongHeader8020B8A0* header;
	if (!(s->active & 0x80000000)) {
		return -1;
	}
	songs = (unsigned int*)lbl_8042CF6C->sequences[bank].data;
	if (songs == 0) {
		return -1;
	}
	for (entry = songs; *entry != 0; entry++) {
		if ((*entry >> 24) == song) {
			goto found;
		}
	}
	return -1;
found:
	header = (SongHeader8020B8A0*)((unsigned char*)songs + (*entry & 0xFFFFFF));
	if (header->tag0 != 0x67636178 || header->tag1 != 0x4D53424D) {
		return -1;
	}
	enabled   = OSDisableInterrupts();
	s->flags4 = 0;
	s->flags4 |= 2;
	if (s->objects != 0) {
		fn_80206834(&s->objects);
		s->objects = 0;
	}
	{
		PoolSequence* q = &s->seq;
		header          = (SongHeader8020B8A0*)((unsigned char*)songs + (*entry & 0xFFFFFF));
		q->f00          = header->f10;
		memset(q, 0, sizeof(PoolSequence));
		q->f04   = header->f1E;
		q->timeB = q->timeA = lbl_8042CF6C->time;
		q->f18              = lbl_804300D0;
		q->param            = param;
		q->start = q->data = (unsigned char*)(header + 1);
	}
	OSRestoreInterrupts(enabled);
	return 0;
}
}
