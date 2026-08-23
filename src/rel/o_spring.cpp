#include "types.h"

struct TObject {
	u8 pad04[0x24];
	virtual void* Destroy(s16 flags);
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char* message);
	virtual void Render();
};

struct SpringSecondary {
	virtual void EditOnChange(void* frame);
};

struct SpringClass : TObject, SpringSecondary {
	virtual void TDisp();
	virtual void* Destroy(s16 flags);
	virtual void Exec();
	virtual void Disp();
	virtual void EditOnChange(void* frame);
};

extern "C" void* __vt__11SpringClass[];
#define springVtable __vt__11SpringClass

namespace spring_assets_unit
{
#include "src/rel/spring_assets.inc"
}

namespace spring_clamp_unit
{
#include "src/rel/spring_clamp.inc"
}

void SpringClass::EditOnChange(void* frame)
{
	spring_clamp_unit::springClampImpl(this, (spring_clamp_unit::Frame*)frame);
}

namespace spring_ctor_unit
{
#include "src/rel/spring_ctor.inc"
}

namespace spring_dtor_unit
{
#include "src/rel/spring_dtor.inc"
}

namespace spring_runtime_unit
{
#include "src/rel/spring_runtime.inc"
}

namespace spring_object_unit
{
#include "src/rel/spring_object.inc"
}
