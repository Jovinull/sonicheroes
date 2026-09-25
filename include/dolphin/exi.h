#ifndef DOLPHIN_EXI_H
#define DOLPHIN_EXI_H

#include <dolphin/os.h>

// The external interface bus API, as declared by the Dolphin SDK (after
// doldecomp/dolsdk2004 include/dolphin/exi.h). EXIBios.c keeps its own
// file-local declarations; this header serves the EXI clients.

#ifdef __cplusplus
extern "C" {
#endif

#define EXI_READ  0
#define EXI_WRITE 1

#define EXI_FREQ_1M  0
#define EXI_FREQ_2M  1
#define EXI_FREQ_4M  2
#define EXI_FREQ_8M  3
#define EXI_FREQ_16M 4
#define EXI_FREQ_32M 5

#define EXI_STATE_DMA_ACCESS 0x01
#define EXI_STATE_IMM_ACCESS 0x02
#define EXI_STATE_SELECTED   0x04
#define EXI_STATE_ATTACHED   0x08
#define EXI_STATE_LOCKED     0x10
#define EXI_STATE_BUSY       (EXI_STATE_DMA_ACCESS | EXI_STATE_IMM_ACCESS)

typedef void (*EXICallback)(s32 chan, OSContext* context);

EXICallback EXISetExiCallback(s32 channel, EXICallback callback);
void EXIInit(void);
BOOL EXILock(s32 channel, u32 device, EXICallback callback);
BOOL EXIUnlock(s32 channel);
BOOL EXISelect(s32 channel, u32 device, u32 frequency);
BOOL EXIDeselect(s32 channel);
BOOL EXIImm(s32 channel, void* buffer, s32 length, u32 type, EXICallback callback);
BOOL EXIImmEx(s32 channel, void* buffer, s32 length, u32 type);
BOOL EXIDma(s32 channel, void* buffer, s32 length, u32 type, EXICallback callback);
BOOL EXISync(s32 channel);
BOOL EXIProbe(s32 channel);
s32 EXIProbeEx(s32 channel);
BOOL EXIAttach(s32 channel, EXICallback callback);
BOOL EXIDetach(s32 channel);
u32 EXIGetState(s32 channel);
s32 EXIGetID(s32 channel, u32 device, u32* id);

#ifdef __cplusplus
}
#endif

#endif
