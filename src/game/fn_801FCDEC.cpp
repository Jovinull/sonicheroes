// Runs the 0x12F atomic plugin handlers on an atomic with pending entries (HYPOTHESIS): flushes
// them with the active flags (then clears those), lets the process handler accept them and,
// when it returns 1 (or is absent), calls the finish handler. Returns the atomic.
#include "game/atomic_plugin_12f.h"

extern "C" {
Atomic12F* fn_801FCDEC(Atomic12F* atomic)
{
	s32 result                = 1;
	Atomic12FPluginData* data = ATOMIC_12F_DATA(atomic);

	if (data->count > 0) {
		if (data->flush) {
			data->flush(atomic, data->block, data->count, data->activeFlags);
			data->activeFlags = 0;
		}
		if (data->process) {
			result = data->process(atomic, data->block, data->count);
		}
		if (result == 1) {
			data->finish(atomic);
		}
	}
	return atomic;
}
}
