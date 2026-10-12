#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjGoalring's destructor (the PS2 build's TObjGoalring::__dt). It takes the
// ring out of the world and frees it, frees the second ring and its back
// part when it has them, frees the last model, and runs the bases down.

class TObjGoalring : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 padB8[0x34];
	RpClump* ring;     // 0xEC
	RpClump* ring2;    // 0xF0
	RpClump* ringBack; // 0xF4
	u8 padF8[0x4];
	RpClump* effect; // 0xFC

	TObjGoalring(TObject* parent);
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void Exec();
	virtual ~TObjGoalring();
};

extern "C" u8* lbl_8042C1D0;

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjGoalring::~TObjGoalring()
{
	if (ring != NULL) {
		fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), ring);
		fn_80150958(ring);
		ring = NULL;
	}
	if (ring2 != NULL) {
		fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), ring2);
		fn_80150958(ring2);
		ring2 = NULL;
		fn_80150958(ringBack);
		ringBack = NULL;
	}
	fn_80150958(effect);
	effect = NULL;
}
