#include "types.h"

// TObjScatteredRing::Exec (the PS2 build's name, by its place in the PS2
// order; scatteredRingExec here): the rings a hurt player drops end when the
// stage tells them to; otherwise they run as TObjRing::Exec does
// (rel/ring_exec.cpp), inlined.

struct RingSubstanceData {
	u8 unk00[0xC8];
	s8 state;      // 0xC8
	u8 unkC9[0xF]; // 0xC9
};

struct RingSubstance : public RingSubstanceData {
	virtual void TDisp();
	virtual void Disp();
	virtual void Exec();
	u8 unkDC[0xC]; // 0xDC
}; // 0xE8

typedef struct Ring {
	u8 unk00[0x4];
	u16 signal;           // 0x04
	u8 unk06[0x22];       // 0x06
	s8 numRings;          // 0x28
	u8 unk29[0x1];        // 0x29
	s8 active;            // 0x2A
	u8 unk2B[0x21];       // 0x2B
	RingSubstance* rings; // 0x4C
} Ring;

extern "C" u8* lbl_8042C180;

static inline void scatteredRingRun(Ring* object)
{
	if (*(s32*)(lbl_8042C180 + 0x40) < 0) {
		if (object->rings == NULL) {
			object->signal |= 1;
			return;
		}
		s32 alive = 0;
		for (s32 i = 0; i < object->numRings; i++) {
			if (object->rings[i].state != 5) {
				object->rings[i].Exec();
				alive++;
			}
		}
		if (alive <= 0) {
			object->active = 0;
			object->signal |= 1;
		}
	}
}

extern "C" void scatteredRingExec(Ring* object)
{
	if ((s8)lbl_8042C180[0x22] != 0) {
		object->signal |= 1;
		return;
	}
	scatteredRingRun(object);
}
