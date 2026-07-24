#include "dolphin/os.h"

typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct OSThreadQueue {
	OSThread* head;
	OSThread* tail;
} OSThreadQueue;

typedef struct OSMutexQueue {
	OSMutex* head;
	OSMutex* tail;
} OSMutexQueue;

typedef struct OSMutexLink {
	OSMutex* next;
	OSMutex* prev;
} OSMutexLink;

struct OSMutex {
	OSThreadQueue queue; // 0x00
	OSThread* thread;    // 0x08
	s32 count;           // 0x0C
	OSMutexLink link;    // 0x10
};

struct OSThread {
	u8 unk_0x000[0x2F4];
	OSMutexQueue queueMutex; // 0x2F4
};

extern void OSWakeupThread(OSThreadQueue* queue);

void __OSUnlockAllMutex(OSThread* thread)
{
	OSMutex* mutex;
	OSMutex* next;

	while (thread->queueMutex.head != NULL) {
		mutex = thread->queueMutex.head;
		next  = mutex->link.next;
		if (next == NULL) {
			thread->queueMutex.tail = NULL;
		} else {
			next->link.prev = NULL;
		}
		thread->queueMutex.head = next;

		mutex->count  = 0;
		mutex->thread = NULL;
		OSWakeupThread(&mutex->queue);
	}
}
