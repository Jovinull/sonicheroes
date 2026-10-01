#ifndef DOLPHIN_OS_OSALARM_H
#define DOLPHIN_OS_OSALARM_H

#include <dolphin/os.h>

// The alarm API, 0x28-byte OSAlarm, for OSAlarm.c's clients (OSAlarm.c keeps
// its own file-local copy of the same layout).

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

struct OSAlarm {
	OSAlarmHandler handler; // 0x00
	u32 tag;                // 0x04
	OSTime fire;            // 0x08
	OSAlarm* prev;          // 0x10
	OSAlarm* next;          // 0x14
	OSTime period;          // 0x18
	OSTime start;           // 0x20
}; // 0x28

void OSInitAlarm(void);
void OSCreateAlarm(OSAlarm* alarm);
void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler);
void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period, OSAlarmHandler handler);
void OSCancelAlarm(OSAlarm* alarm);

#ifdef __cplusplus
}
#endif

#endif
