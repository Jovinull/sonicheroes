// TObjChao (the PS2 build's name), CHAO OBJECT: the chao in its cage that the
// team's leader frees, in the thirteen stage modules that share it. Only what
// the matched members use is laid out; its constructor (chaoCtor) and Exec stay
// assembly. The bases are the usual placed object's: the placement base at 0x28
// and the collision block at 0x30.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

class TObjChao : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 padB8[0xE4 - 0xB8];
	RpClump* clump; // 0xE4
	u8 padE8[0x4];  // 0xE8
	TObject* unkEC; // 0xEC: deleted with the chao

	void SearchCage();
	s32 CheckTouchedByLeader();

	// Exec first: it is the key function and no unit defines it, so the units
	// that define the others do not emit the vtable.
	virtual void Exec();
	virtual ~TObjChao();
	virtual void PDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};
