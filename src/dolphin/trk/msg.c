#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msg.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"

// MetroTRK msg.c: the framed packet sender, 0x801C98B8 to 0x801C9A94.
// Boundaries: every function matched by instruction shape against the
// reference compiled with the MetroTRK flags, in link order.
// Reference: mariopartyrd/marioparty4 src/TRK_MINNOW_DOLPHIN/msg.c (public
// decompilation of the same MetroTRK build). Built with GC/1.3; see the
// TRK_MINNOW_DOLPHIN entry in configure.py.
// The UART writers are called TRKWriteUART1 and TRKFlushUART here, as the
// existing dolphin_trk.c names them.

// Incorrect signature? Should be u8.
UARTError TRKWriteUART1(s8 arg0);

DSError TRKMessageSend(TRK_Msg* msg)
{
	u8 var_r30;
	u8 var_r28;
	u8 var_r28_2;
	s32 var_r3;
	s32 i;

	var_r30 = 0;
	for (i = 0; i < msg->m_msgLength; i++) {
		var_r30 = var_r30 + msg->m_msg[i];
	}
	var_r30 = var_r30 ^ 0xFF;
	var_r3  = TRKWriteUART1(0x7E);
	if (var_r3 == 0) {
		for (i = 0; i < msg->m_msgLength; i++) {
			var_r28 = msg->m_msg[i];
			if (var_r28 == 0x7E || var_r28 == 0x7D) {
				var_r3 = TRKWriteUART1(0x7D);
				var_r28 ^= 0x20;
				if (var_r3 != 0) {
					break;
				}
			}
			var_r3 = TRKWriteUART1(var_r28);
			if (var_r3 != 0) {
				break;
			}
		}
	}
	if (var_r3 == 0) {
		var_r28_2 = var_r30;
		for (i = 0; i < 1; i++) {
			if (var_r28_2 == 0x7E || var_r28_2 == 0x7D) {
				var_r3 = TRKWriteUART1(0x7D);
				var_r28_2 ^= 0x20;
				if (var_r3 != 0) {
					break;
				}
			}
			var_r3 = TRKWriteUART1(var_r28_2);
			if (var_r3 != 0) {
				break;
			}
		}
	}
	if (var_r3 == 0) {
		var_r3 = TRKWriteUART1(0x7E);
	}
	if (var_r3 == 0) {
		var_r3 = TRKFlushUART();
	}
	return var_r3;
}
