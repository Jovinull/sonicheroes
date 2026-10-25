// TObjPalm's destructor, out of line, as TObjYajirusi's (rel/yajirusi_dtor.cpp):
// for its 2 parts it takes the clump out of its world slot (fn_8015BBF8) if it
// was added, destroys it (fn_80150958) and clears both fields. The destructor
// is declared after the class's first other virtual in rel/palm_class.inc, so
// this unit does not emit the vtable.

#include "src/rel/palm_class.inc"

extern "C" void fn_80150958(RpClump* clump);

TObjPalm::~TObjPalm()
{
	for (int i = 0; i < 2; i++) {
		if (parts[i].added == 1) {
			fn_8015BBF8(
			    *(void**)(lbl_8042C1D0 + 0x7250 + palmModelFiles[i].world * 4), parts[i].clump);
			parts[i].added = 0;
		}
		fn_80150958(parts[i].clump);
		parts[i].clump = NULL;
	}
}
