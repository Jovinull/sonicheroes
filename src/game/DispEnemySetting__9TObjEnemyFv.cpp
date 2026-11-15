// TObjEnemy::DispEnemySetting (symbol name from the retail map). The GameCube body is empty:
// the debug display of the enemy set parameters is compiled out (HYPOTHESIS: it was a
// development-only view, like the other empty Debug hooks of TObject).
#include "types.h"

// Minimal local view: only the member being defined is declared (see game/enemy/e_link.h for
// the fuller TObjEnemy shape).
class TObjEnemy
{
public:
	void DispEnemySetting();
};

void TObjEnemy::DispEnemySetting() { }
