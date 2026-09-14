#ifndef DOLPHIN_AX_H
#define DOLPHIN_AX_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AxVoice AxVoice;

typedef struct AxVoiceRate {
	u16 ratioHigh;
	u16 ratioLow;
	u16 fraction;
	s16 samples[4];
} AxVoiceRate;

void fn_801E221C(AxVoice* voice);
AxVoice* fn_801E229C(s32 priority, void (*callback)(AxVoice*), s32 userContext);
void fn_801E48D0(AxVoice* voice, s32 rate);
void fn_801E4994(AxVoice* voice, s32 state);
void fn_801E4C44(AxVoice* voice, void* addressParameters);
void fn_801E4DF8(AxVoice* voice, AxVoiceRate* rateParameters);
void fn_801E7B08(AxVoice* voice, s32 type, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void fn_801E8984(AxVoice* voice);
void fn_801E89A4(AxVoice* voice, s32 volume);
void fn_801E89CC(AxVoice* voice, s32 pan);

#ifdef __cplusplus
}
#endif

#endif
