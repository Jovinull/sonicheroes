// Drains the MIDI event queue of an audio pool slot (see game/audio_system.h). Each event packs
// status (top byte), data1, data2 and a signed extra byte; the queue is popped with interrupts
// disabled. Note on (0x90 with data2 != 0) appends a note object made by fn_80206948; note off
// (0x80, or 0x90 with data2 == 0) releases the channel's notes with that key unless the channel
// sustains; 0xB0 goes to fn_802094A4, 0xC0 sets the program and 0xE0 the pitch bend (f1C, with
// f2C = f1C - 0x2000). Note-entry layouts are inferred; as in retail, a removed note node is still
// used to step to the next one.
// NonMatching: 191 of 192 instructions; registers and control flow agree. Retail stores the
// pitch bend through a separate indexed address (addi + stwx) before re-forming the channel
// address for f2C; MWCC reuses one address, so one instruction is missing and later branch
// offsets shift (34 word diffs).
#include "game/audio_system.h"

struct Voice802096B0 {
	unsigned char pad0[0xD8];
	int state; // 0xD8
};

extern "C" {
PoolListNode* fn_80206328(PoolListNode** list, PoolListNode* prev);
PoolListNode* fn_802068E4(PoolListNode** list, PoolListNode* prev);
void fn_8020685C(PoolListNode** list, PoolListNode* node);
PoolListNode* fn_80206904(PoolListNode** list, void* data);
PoolObject* fn_80206948(
    PoolSlot* s, unsigned int ch, unsigned int key, unsigned int velocity, int extra);
void fn_802094A4(PoolSlot* s, unsigned char ch, unsigned char cc, unsigned char value);

static inline void NoteOff(PoolSlot* s, unsigned int ch, unsigned int key)
{
	PoolListNode* node;
	if (s->channels[ch].f00 & 1) {
		return;
	}
	for (node = 0; (node = fn_802068E4(&s->objects, node)) != 0;) {
		PoolObject* o = (PoolObject*)node->data;
		if (o == 0 || o->channel != ch || o->key != key) {
			continue;
		}
		if (s->active & 0x40000000) {
			fn_8020685C(&s->objects, node);
		} else {
			PoolListNode* v;
			for (v = 0; (v = fn_80206328(&o->entries, v)) != 0;) {
				Voice802096B0* voice = (Voice802096B0*)v->data;
				if (voice != 0 && voice->state < 4) {
					voice->state = 4;
				}
			}
		}
	}
}

void fn_802096B0(PoolSlot* s)
{
	while (s->eventCount != 0) {
		BOOL enabled = OSDisableInterrupts();
		unsigned int ev;
		unsigned char ch;
		unsigned char d1;
		unsigned char d2;
		int extra;
		s->eventCount--;
		ev = s->events[s->eventRead];
		s->eventRead++;
		s->eventRead %= 0x400;
		OSRestoreInterrupts(enabled);
		ch    = (ev >> 24) & 0xF;
		d1    = (ev >> 16) & 0xFF;
		d2    = (ev >> 8) & 0xFF;
		extra = (signed char)(ev & 0xFF);
		switch ((ev >> 24) & 0xF0) {
			case 0x80:
				NoteOff(s, ch, d1);
				break;
			case 0x90:
				if (d2 != 0) {
					PoolListNode* node = fn_80206904(&s->objects, 0);
					PoolObject* o;
					if (node == 0) {
						break;
					}
					o = fn_80206948(s, ch, d1, d2, extra);
					if (o == 0) {
						fn_8020685C(&s->objects, node);
						break;
					}
					o->slot    = s;
					o->key     = d1;
					o->channel = ch;
					node->data = o;
				} else {
					NoteOff(s, ch, d1);
				}
				break;
			case 0xA0:
				break;
			case 0xB0:
				fn_802094A4(s, ch, d1, d2);
				break;
			case 0xC0:
				s->channels[ch].f0C = d1 & 0x7F;
				break;
			case 0xD0:
				break;
			case 0xE0: {
				unsigned short bend = ((d2 & 0x7F) << 7) + (d1 & 0x7F);
				s->channels[ch].f1C = bend & 0x3FFF;
				s->channels[ch].f2C = s->channels[ch].f1C - 0x2000;
			} break;
		}
	}
}
}
