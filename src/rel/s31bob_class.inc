// TObjS31Bob, shared by rel/s31bob_create.cpp, which defines S31BOB_CTOR
// as inline so its factory inlines the constructor, and rel/s31bob_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* s31bobObjectdummyClassName;
extern "C" TObject* lbl_8042C110;

class TObjS31Bob : public TObject, public TObjSetObj
{
public:
	TObjS31Bob(TObject* parent);
	virtual ~TObjS31Bob();
	virtual void Exec();
	virtual void Disp();
};

S31BOB_CTOR TObjS31Bob::TObjS31Bob(TObject* parent)
    : TObject(parent)
{
	ClassName = s31bobObjectdummyClassName;
	DispTime  = 0x30;
}
