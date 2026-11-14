// Places the audio system block (see game/audio_system.h) at the 32-byte aligned start of mem,
// or of memSize bytes taken from the current OS heap when mem is null (lbl_8042CF70 records that
// the caller supplied the memory). The rest of the memory becomes the audio heap, and the AXFX
// effects get their default parameters. Hangs after reporting lbl_8023D5F8 when the OS heap is
// exhausted; reports lbl_8023D628 otherwise.
#include "game/audio_system.h"

extern "C" {
extern const float lbl_804300B0; // 3.0f
extern const float lbl_804300B4; // 0.1f
extern const float lbl_804300B8; // 0.5f
extern const float lbl_804300BC; // 0.3f
extern char lbl_8023D5F8[];
extern char lbl_8023D628[];
extern void* lbl_8042CF68;
extern int lbl_8042CF70;
extern volatile int __OSCurrHeap;
void* OSAllocFromHeap(int heap, unsigned int size);
void* memset(void* dst, int value, unsigned long n);
void fn_80205DF4(void* mem, unsigned int size);

static inline void* GetAudioMemory(void* mem, unsigned int size)
{
	if (mem != 0) {
		lbl_8042CF70 = 1;
		return mem;
	}
	return OSAllocFromHeap(__OSCurrHeap, size);
}

void fn_8020A3EC(void* mem, unsigned int memSize)
{
	BOOL enabled = OSDisableInterrupts();
	unsigned char* heap;
	mem = GetAudioMemory(mem, memSize);
	if (mem == 0) {
		OSReport(lbl_8023D5F8, memSize);
		while (1) {
		}
	}
	OSReport(lbl_8023D628, memSize);
	lbl_8042CF68         = mem;
	lbl_8042CF6C         = (PoolSystem*)(((u32)mem + 0x1F) & ~0x1F);
	lbl_8042CF6C->f00    = 0;
	lbl_8042CF6C->f13A38 = 0;
	OSRestoreInterrupts(enabled);
	memset(lbl_8042CF6C, 0, sizeof(PoolSystem));
	heap = (unsigned char*)(((u32)lbl_8042CF6C + sizeof(PoolSystem) + 0x1F) & ~0x1F);
	fn_80205DF4(heap, memSize - (heap - (unsigned char*)mem));
	lbl_8042CF6C->reverbStd.tempDisableFX = 0;
	lbl_8042CF6C->reverbStd.time          = lbl_804300B0;
	lbl_8042CF6C->reverbStd.preDelay      = lbl_804300B4;
	lbl_8042CF6C->reverbStd.damping       = lbl_804300B8;
	lbl_8042CF6C->reverbStd.coloration    = lbl_804300B8;
	lbl_8042CF6C->reverbStd.mix           = lbl_804300B8;
	lbl_8042CF6C->reverbHi.tempDisableFX  = 0;
	lbl_8042CF6C->reverbHi.time           = lbl_804300B0;
	lbl_8042CF6C->reverbHi.preDelay       = lbl_804300B4;
	lbl_8042CF6C->reverbHi.damping        = lbl_804300B8;
	lbl_8042CF6C->reverbHi.coloration     = lbl_804300B8;
	lbl_8042CF6C->reverbHi.crosstalk      = lbl_804300BC;
	lbl_8042CF6C->reverbHi.mix            = lbl_804300B8;
	lbl_8042CF6C->chorus.baseDelay        = 15;
	lbl_8042CF6C->chorus.variation        = 0;
	lbl_8042CF6C->chorus.period           = 500;
	lbl_8042CF6C->delay.delay[0]          = 500;
	lbl_8042CF6C->delay.delay[1]          = 500;
	lbl_8042CF6C->delay.delay[2]          = 500;
	lbl_8042CF6C->delay.feedback[0]       = 50;
	lbl_8042CF6C->delay.feedback[1]       = 50;
	lbl_8042CF6C->delay.feedback[2]       = 50;
	lbl_8042CF6C->delay.output[0]         = 100;
	lbl_8042CF6C->delay.output[1]         = 100;
	lbl_8042CF6C->delay.output[2]         = 100;
}
}
