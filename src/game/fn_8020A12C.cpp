// Initialises the audio system (see game/audio_system.h): fn_8020A3EC sets up the block from mem
// and memSize, then the ARAM arena (aramSize bytes from ARAlloc, 32-byte aligned, starting with
// 0x500 zeroed bytes), the region sizes (the first table is overwritten by fn_802061B4 before
// any region is reserved), the voice entries (voiceCount AX voices), the AXFX heap hooks and the
// four aux effects. Reports the free arena size with lbl_8023D5E0 and returns 0.
#include "game/audio_system.h"
#include "dolphin/ar.h"

extern "C" {
extern const float lbl_804300A8; // 0.0f
extern const float lbl_804300AC; // 1.0f
extern char lbl_8023D5E0[];
void* memset(void* dst, int value, unsigned long n);
void fn_8020A3EC(void* mem, unsigned int memSize);
void fn_802059B4(
    u32 source, u32 destination, u32 length, PoolRequestCallback callback, unsigned int arg);
void fn_802061B4(void);
int fn_80206104(int id, int size);
void fn_80208E28(void);
void* fn_80205CBC(unsigned int size);
void fn_80205C10(void* p);
void AXFXSetHooks(void* (*alloc)(unsigned int size), void (*free)(void* p));

static inline void ReserveDefaultRegions(void)
{
	int i;
	for (i = 0; i < 0x10; i++) {
		if (lbl_8042CF6C->regionDefaults[i] != 0) {
			fn_80206104(i, (lbl_8042CF6C->regionDefaults[i] + 0x1F) & ~0x1F);
		}
	}
}

int fn_8020A12C(void* mem, int voiceCount, unsigned int memSize, unsigned int aramSize)
{
	unsigned char* zero;
	fn_8020A3EC(mem, memSize);
	lbl_8042CF6C->size       = sizeof(PoolSystem);
	lbl_8042CF6C->f2C        = lbl_804300A8;
	lbl_8042CF6C->arqOwner   = 0xF;
	lbl_8042CF6C->voiceCount = voiceCount;
	lbl_8042CF6C->aramSize   = aramSize;
	lbl_8042CF6C->aramBase   = ARAlloc(lbl_8042CF6C->aramSize);
	lbl_8042CF6C->arenaNext  = (lbl_8042CF6C->aramBase + 0x1F) & ~0x1F;
	lbl_8042CF6C->arenaFree
	    = lbl_8042CF6C->aramSize - (lbl_8042CF6C->arenaNext - lbl_8042CF6C->aramBase);
	zero = (unsigned char*)(((u32)lbl_8042CF6C->zeroBuffer + 0x1F) & ~0x1F);
	memset(zero, 0, 0x500);
	fn_802059B4((u32)zero, lbl_8042CF6C->arenaNext, 0x500, 0, 0);
	lbl_8042CF6C->aramZero = lbl_8042CF6C->arenaNext;
	lbl_8042CF6C->arenaNext += 0x500;
	lbl_8042CF6C->arenaFree -= 0x500;
	lbl_8042CF6C->f13A44             = lbl_804300AC;
	lbl_8042CF6C->regionDefaults[0]  = 512000;
	lbl_8042CF6C->regionDefaults[1]  = 460000;
	lbl_8042CF6C->regionDefaults[2]  = 360000;
	lbl_8042CF6C->regionDefaults[3]  = 400000;
	lbl_8042CF6C->regionDefaults[4]  = 360000;
	lbl_8042CF6C->regionDefaults[5]  = 360000;
	lbl_8042CF6C->regionDefaults[6]  = 140000;
	lbl_8042CF6C->regionDefaults[7]  = 100000;
	lbl_8042CF6C->regionDefaults[8]  = 170016;
	lbl_8042CF6C->regionDefaults[9]  = 200000;
	lbl_8042CF6C->regionDefaults[10] = 240000;
	lbl_8042CF6C->regionDefaults[11] = 24000;
	lbl_8042CF6C->regionDefaults[12] = 400000;
	lbl_8042CF6C->regionDefaults[13] = 40000;
	fn_802061B4();
	ReserveDefaultRegions();
	OSReport(lbl_8023D5E0, lbl_8042CF6C->arenaFree);
	lbl_8042CF6C->f44 = 1;
	fn_80208E28();
	AXFXSetHooks(fn_80205CBC, fn_80205C10);
	AXFXReverbStdInit(&lbl_8042CF6C->reverbStd);
	AXFXReverbHiInit(&lbl_8042CF6C->reverbHi);
	AXFXChorusInit(&lbl_8042CF6C->chorus);
	AXFXDelayInit(&lbl_8042CF6C->delay);
	lbl_8042CF6C->f00 = 1;
	return 0;
}
}
