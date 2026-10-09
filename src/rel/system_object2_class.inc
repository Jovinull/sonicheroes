// TObjSystem2, shared by rel/system_object2_create.cpp, which defines SYSTEM_OBJECT2_CTOR
// as inline so its factory inlines the constructor, and rel/system_object2_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* systemObject2ClassName;
extern "C" TObject* lbl_8042C110;

class TObjSystem2 : public TObject, public TObjSetObj
{
public:
	TObjSystem2(TObject* parent);
	virtual void Exec();
	virtual ~TObjSystem2();
	virtual void Disp();
};

SYSTEM_OBJECT2_CTOR TObjSystem2::TObjSystem2(TObject* parent)
    : TObject(parent)
{
	ClassName = systemObject2ClassName;
	DispTime  = 0x30;
}
