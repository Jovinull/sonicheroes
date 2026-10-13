#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjPropeller's destructor (the PS2 build's TObjPropeller::__dt): it takes
// its three models out of the world, frees them and runs the bases down.

class TObjPropeller : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 padB8[0x98];
	RpClump* models[3]; // 0x150

	TObjPropeller(TObject* parent);
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void Exec();
	virtual ~TObjPropeller();
};

extern "C" u8* lbl_8042C1D0;

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

TObjPropeller::~TObjPropeller()
{
	for (int i = 0; i < 3; i++) {
		if (models[i] != NULL) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7260), models[i]);
			fn_80150958(models[i]);
			models[i] = NULL;
		}
	}
}
