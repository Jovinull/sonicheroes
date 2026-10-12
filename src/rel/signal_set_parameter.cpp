#include "types.h"

// TObjSignal::SetParameter's out-of-line copy (signalSetParameter here). The
// body is in rel/signal_class.inc, where it is inline for signalExec; this unit
// defines it plain so the copy is emitted.

#define SIGNAL_SET_PARAMETER_INLINE
#include "src/rel/signal_class.inc"
