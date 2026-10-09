// TObjTrainRollTunnel's destructor, out of line. For its 6 parts it takes the
// clump out of its world slot (fn_8015BBF8) if it was added, destroys it
// (fn_80150958) and clears both fields. The class is shared through
// train_roll_tunnel_class.inc, where the destructor is declared after the
// class's first other virtual so this unit does not emit the vtable.

#define TRAIN_ROLL_TUNNEL_CTOR inline
#include "src/rel/train_roll_tunnel_class.inc"

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjTrainRollTunnel::~TObjTrainRollTunnel()
{
	for (int i = 0; i < 6; i++) {
		if (parts[i].added == 1) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + trainRollTunnelModelFiles[i].world * 4),
			    parts[i].clump);
			parts[i].added = 0;
		}
		fn_80150958(parts[i].clump);
		parts[i].clump = NULL;
	}
}
