#include "PowerPC_EABI_Support/MetroTRK/trk.h"

// MetroTRK target options, 0x801CFF4C to 0x801CFF68: the serial I/O switch
// the MSL console routines consult.
// Reference: mariopartyrd/marioparty4 src/TRK_MINNOW_DOLPHIN/target_options.c.
// Built with GC/1.3 and the MetroTRK flags; see the TRK_MINNOW_DOLPHIN entry in
// configure.py.
//
static u8 bUseSerialIO;

void SetUseSerialIO(u8 sio)
{
	bUseSerialIO = sio;
}

u8 GetUseSerialIO(void)
{
	return bUseSerialIO;
}
