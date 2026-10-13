#include "types.h"

// TObjCannon::CalcBarrelPosition (cannonCalcBarrelPosition here), the
// out-of-line copy nothing calls. It builds the barrel's matrix from the two
// barrel angles (about X, then Y) at the barrel's pivot (the module's offset,
// lowered a little the first time) on the cannon, and turns the barrel tip into
// the cannon's tip position; the matrix goes to the caller when asked for. Then
// it builds it again at the unlowered pivot for the second tip position.
//
// The first offset and the tip are initialised from the module's vectors, which
// MWCC copies as words; the second offset is assigned, which it copies as floats.

#define CANNON_CALC_BARREL_INLINE
#include "src/rel/cannon_class.inc"
