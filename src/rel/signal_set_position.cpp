#include "types.h"

// TObjSignal::SetPosition's out-of-line copy (signalSetPosition here). The body
// is in rel/signal_class.inc, where it is inline for signalExec; this unit
// defines it plain so the copy is emitted.

#define SIGNAL_SET_POSITION_INLINE
#include "src/rel/signal_class.inc"
