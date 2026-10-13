#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjFormGate's destructor (the PS2 build's TObjFormGate::__dt): it frees the
// gate's three models and runs the bases down.

class TObjFormGate : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 padB8[0x34];
	RpClump* models[3]; // 0xEC

	TObjFormGate(TObject* parent);
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void Exec();
	virtual ~TObjFormGate();
};

extern "C" void fn_80150958(RpClump* clump);

TObjFormGate::~TObjFormGate()
{
	if (models[0] != NULL) {
		fn_80150958(models[0]);
		models[0] = NULL;
	}
	if (models[1] != NULL) {
		fn_80150958(models[1]);
		models[1] = NULL;
	}
	if (models[2] != NULL) {
		fn_80150958(models[2]);
		models[2] = NULL;
	}
}
