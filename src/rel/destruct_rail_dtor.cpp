// TObjDestructRail's destructor, out of line. For each of its two parts that
// has a clump it takes the clump out of its world slot (fn_8015BBF8) if it was
// added, destroys it (fn_80150958) and clears both fields; then it marks the
// placement's original work (a halfword flag at +2), read before the loop as
// in rel/train_change_rail_dtor.cpp. Inside the clump test the constant 0 is
// rematerialized for each store, unlike the unconditional part loops
// (rel/bridge_dtor.cpp). The class is shared through destruct_rail_class.inc,
// where the destructor is declared after the class's first other virtual so
// this unit does not emit the vtable.

#define DESTRUCT_RAIL_CTOR inline
#include "src/rel/destruct_rail_class.inc"

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjDestructRail::~TObjDestructRail()
{
	u16* original = (u16*)ObjParam->originalWork;

	for (int i = 0; i < 2; i++) {
		if (parts[i].clump != NULL) {
			if (parts[i].added == 1) {
				fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + destructRailModelFiles[i].world * 4),
				    parts[i].clump);
				parts[i].added = 0;
			}
			fn_80150958(parts[i].clump);
			parts[i].clump = NULL;
		}
	}
	original[1] = 1;
}
