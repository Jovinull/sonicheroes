#ifndef DOLPHIN_OS_OSTHREAD_H
#define DOLPHIN_OS_OSTHREAD_H

// Minimal shim for the GX FIFO header, which returns OSThread* from a couple of
// entry points. GX never dereferences the thread, so an incomplete type is
// enough; the full definition lives with the thread implementation.

typedef struct OSThread OSThread;

#endif
