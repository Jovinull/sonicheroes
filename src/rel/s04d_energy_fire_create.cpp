#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s04dEnergyFireCreate, the factory rel/s04d_energy_fire_register.cpp puts in
// the editor record: a new TObjS04EnergyFire (the class name its constructor
// stores), whose collision block (its third base) takes the module's shape and
// the set data's first parameter as its size. As in rel/sample1_create.cpp,
// the allocation is a real new-expression of the class; the parameter block
// pointer is read before the class name.

extern "C" char* CL_TObjS04EnergyFire;
extern "C" CCL_INFO s04dEnergyFireCclInfo;
extern "C" TObject* lbl_8042C110;

class TObjS04EnergyFire : public TObject, public TObjSetObj, public C_COLLI
{
public:
	TObjS04EnergyFire(TObject* parent)
	    : TObject(parent)
	{
		f32* param = (f32*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS04EnergyFire;
		DispTime  = 0xB8;
		Init(&s04dEnergyFireCclInfo, 1, 5);
		info->a = param[0];
		CalcRange();
	}
	virtual ~TObjS04EnergyFire();
};

extern "C" void s04dEnergyFireCreate(void)
{
	new TObjS04EnergyFire(lbl_8042C110);
}
