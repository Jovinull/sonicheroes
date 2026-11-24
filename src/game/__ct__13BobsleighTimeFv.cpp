// BobsleighTime::BobsleighTime() (CORROBORATED by the PS2 build, see fn_80116764.cpp): the
// bobsleigh time display. Builds the TObject under lbl_8042C118, clears its state words, then
// opens the language archive lbl_80288EAC[language] and loads, through a 0x4B000-byte work buffer,
// the texture dictionary (entry 2, made current) and the 2D animation (Rt2dMaestro, entry 4,
// prepared with fn_800A8EC4 / fn_800A8CB8) into lbl_8042C694 / lbl_8042C698, which the destructor
// releases. The field names are inferred.
#include "game/one.h"

class TObject;

struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};

// Local view of TObject: the vtable pointer is a data member (BobsleighTime's vtable is in another
// split) and the destructor is declared for the exception cleanup of the base.
class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	~TObject();

	void* vtable; // 0x18
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
};

struct GameState80116818 {
	u8 pad0[0x13];
	s8 language; // 0x13
};

extern "C" {
extern u8 __vt__13BobsleighTime[];
extern TObject* lbl_8042C118;
extern GameState80116818* lbl_8042C180;
extern char* lbl_80288EAC[];
extern RwTexDictionary* lbl_8042C694;
extern Rt2dMaestro* lbl_8042C698;
void* fn_80012994(u32 size);
void fn_800126C8(void* buffer);
void fn_801A4C84(RwTexDictionary* dictionary);
void fn_800A8EC4(Rt2dMaestro* maestro);
void fn_800A8CB8(Rt2dMaestro* maestro);
}

class BobsleighTime : public TObject
{
public:
	BobsleighTime();
	~BobsleighTime();

	u8 pad28[0x2C - 0x28];
	s32 f2C; // 0x2C
	u8 pad30[0x4C - 0x30];
	s32 f4C; // 0x4C
	s32 f50; // 0x50
};

BobsleighTime::BobsleighTime()
    : TObject(lbl_8042C118)
{
	vtable       = __vt__13BobsleighTime;
	f2C          = -1;
	f4C          = -1;
	f50          = 0;
	ONEFILE* one = new ONEFILE(lbl_80288EAC[lbl_8042C180->language], 0);
	if (one != NULL) {
		void* buffer = fn_80012994(0x4B000);
		lbl_8042C694 = one->OneFileLoadTextureDictionay(2, buffer);
		fn_801A4C84(lbl_8042C694);
		lbl_8042C698 = one->OneFileLoadMaestro(4, buffer);
		if (lbl_8042C698 != NULL) {
			fn_800A8EC4(lbl_8042C698);
			fn_800A8CB8(lbl_8042C698);
		}
		if (buffer != NULL) {
			fn_800126C8(buffer);
		}
		delete one;
	}
}
