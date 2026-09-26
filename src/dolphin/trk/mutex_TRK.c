#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/mutex_TRK.h"

// MetroTRK mutex_TRK.c: the no-op mutex stubs, 0x801CDAD4 to 0x801CDAEC.
// Boundaries: every function matched by instruction shape against the
// reference compiled with the MetroTRK flags, in link order.
// Reference: mariopartyrd/marioparty4 src/TRK_MINNOW_DOLPHIN/mutex_TRK.c (public
// decompilation of the same MetroTRK build). Built with GC/1.3; see the
// TRK_MINNOW_DOLPHIN entry in configure.py.

DSError TRKInitializeMutex(void*)
{
	return DS_NoError;
}

DSError TRKAcquireMutex(void*)
{
	return DS_NoError;
}

DSError TRKReleaseMutex(void*)
{
	return DS_NoError;
}
