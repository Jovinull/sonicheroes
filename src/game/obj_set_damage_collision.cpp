#include "types.h"

// The PS2 beta symbols place these functions together under the
// TObjSetDamageCollision class immediately before TEnemyParalysis. The retail
// GameCube text and exception-table boundaries preserve the same adjacency,
// although only the display, execution, and startup entry points remain.

class TObject
{
protected:
	u8 padding[0x18];

public:
	virtual ~TObject();
};

class TObjSetDamageCollision : public TObject
{
public:
	virtual ~TObjSetDamageCollision();
	void TDisp();
	void Exec();
};

TObjSetDamageCollision* lbl_8042C640[2];

void TObjSetDamageCollision::TDisp() { }

void TObjSetDamageCollision::Exec()
{
	if (lbl_8042C640[0] != NULL) {
		delete lbl_8042C640[0];
		lbl_8042C640[0] = NULL;
	}
}

void startObjSetDamageCollision()
{
	lbl_8042C640[0] = NULL;
}
