#include "types.h"

struct PARTICLE_INSTANCE;

// Only the part of PARTICLE_MATERIAL this unit needs. Its destructor (game/__dt__17PARTICLE_MATERIALFv.cpp)
// is the first virtual function, so the class's vtable is emitted with it, not here.
class PARTICLE_MATERIAL
{
public:
	virtual ~PARTICLE_MATERIAL();
	virtual void Disp(PARTICLE_INSTANCE*);
};

void PARTICLE_MATERIAL::Disp(PARTICLE_INSTANCE*) { }
