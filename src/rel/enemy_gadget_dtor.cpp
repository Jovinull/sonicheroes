// TEnemyGadget's destructor (inline in game/enemy/e_gadget.h), the copy an
// enemy translation unit of the stage module emits; it stores main's vtable.
// The class is declared here with only what the destructor needs, the
// destructor after the first other virtual so this unit does not emit the
// vtable (see rel/key_object_class.inc).

#include "game/effect/eff_bomb.h"

class TEnemyGadget : public TObject
{
public:
	virtual void Exec();
	virtual ~TEnemyGadget();
};

TEnemyGadget::~TEnemyGadget() { }
