// TObjChao (the PS2 build's name), CHAO OBJECT: the chao in its cage that the
// team's leader frees, in the thirteen stage modules that share it. Only what
// the matched members use is laid out; Exec stays assembly. The bases are the
// usual placed object's: the placement base at 0x28 and the collision block at
// 0x30.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

class TObjChao : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;                          // 0xB8
	RwV3d worldPos;                     // 0xC4: the frame's position after SetPosition
	s32 state;                          // 0xD0: 2 when freed already, else 1
	f32 offset;                         // 0xD4: how far from the cage the chao sits
	f32 spin;                           // 0xD8: added to the angle every frame
	s32 unkDC;                          // 0xDC
	f32 angle;                          // 0xE0
	RpClump* clump;                     // 0xE4
	struct RpHAnimHierarchy* hierarchy; // 0xE8
	TObject* unkEC;                     // 0xEC: deleted with the chao

	TObjChao(TObject* parent);
	void SearchCage();
	void SetPosition();
	s32 CheckTouchedByLeader();

	// Exec first: it is the key function and no unit defines it, so the units
	// that define the others do not emit the vtable.
	virtual void Exec();
	virtual ~TObjChao();
	virtual void PDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};
