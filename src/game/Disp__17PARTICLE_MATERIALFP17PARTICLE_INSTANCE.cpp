// PARTICLE_MATERIAL::Disp(PARTICLE_INSTANCE*) (symbol name from the retail map). The base
// material draws nothing: the GameCube body is empty (HYPOTHESIS: derived materials override it).
#include "types.h"

class PARTICLE_INSTANCE;

// Minimal local view: only the member being defined is declared. Whether Disp is virtual is
// UNKNOWN here; declaring it non-virtual keeps this unit from emitting a vtable.
class PARTICLE_MATERIAL
{
public:
	void Disp(PARTICLE_INSTANCE* instance);
};

void PARTICLE_MATERIAL::Disp(PARTICLE_INSTANCE* instance) { }
