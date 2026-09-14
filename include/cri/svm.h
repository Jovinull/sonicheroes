#ifndef CRI_SVM_H
#define CRI_SVM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef s32 (*SvmServerFunc)(void* object);
typedef void (*SvmLockFunc)(void* object);
typedef void (*SvmErrorFunc)(void* object, const char* message);

u32 fn_802218A8(s32* value);
void fn_802219BC(void);
void fn_80221A64(void);
s32 fn_80221AFC(void);
s32 fn_80221B8C(void);
s32 fn_80221C1C(void);
s32 fn_80221CAC(void);
void fn_80221D3C(SvmLockFunc function, void* object);
void fn_80221D4C(SvmLockFunc function, void* object);
void fn_80221D5C(SvmErrorFunc function, void* object);
void fn_80221E4C(s32 id);
void fn_80221E90(s32 id, SvmServerFunc function, void* object);
void fn_80221F94(s32 type, s32 id, SvmServerFunc function, void* object);
void fn_80222148(s32 type, s32 id);
s32 fn_80222290(s32 type, SvmServerFunc function, void* object);
void fn_8022240C(const char* message);
void fn_80222464(const char* format, ...);
void fn_8022253C(void);
void fn_802225CC(void);
void fn_8022265C(void);
void fn_802226EC(void);
void fn_8022277C(void);
void fn_802227E4(void);
void fn_8022284C(void);
void fn_802228B4(void);
void fn_8022291C(void);
void fn_802229AC(void);

#ifdef __cplusplus
}
#endif

#endif
