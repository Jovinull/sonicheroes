#ifndef DOLPHIN_ARQ_H
#define DOLPHIN_ARQ_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ARQCallback)(u32 request);

typedef struct ARQRequest {
	struct ARQRequest* next;
	u32 owner;
	u32 type;
	u32 priority;
	u32 source;
	u32 dest;
	u32 length;
	ARQCallback callback;
} ARQRequest;

void ARQPostRequest(ARQRequest* request, u32 owner, u32 type, u32 priority, u32 source,
    u32 destination, u32 length, ARQCallback callback);

#ifdef __cplusplus
}
#endif

#endif
