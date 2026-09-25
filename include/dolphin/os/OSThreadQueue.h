#ifndef DOLPHIN_OS_OSTHREADQUEUE_H
#define DOLPHIN_OS_OSTHREADQUEUE_H

#include <dolphin/os/OSThread.h>

// The thread wait queue and its sleep/wakeup API, for OSThread.c's clients.

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSThreadQueue {
	OSThread* head; // 0x00
	OSThread* tail; // 0x04
} OSThreadQueue;

void OSInitThreadQueue(OSThreadQueue* queue);
void OSSleepThread(OSThreadQueue* queue);
void OSWakeupThread(OSThreadQueue* queue);

#ifdef __cplusplus
}
#endif

#endif
