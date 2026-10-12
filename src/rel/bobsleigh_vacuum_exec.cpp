#include "types.h"

// TObjBobsleighVacuum::Exec (the PS2 build's name): see
// rel/bobsleigh_volume_exec.inc.

#include "src/rel/bobsleigh_volume_exec.inc"

extern "C" void Exec__19TObjBobsleighVacuumFv(BobsleighVolume* object)
{
	bobsleighVolumeExec(object);
}
