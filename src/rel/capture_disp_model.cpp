#include "types.h"

// The capture enemy's model display (captureDispModel here), the same in the
// seven stage modules that carry the capture: its two first texture sets get
// ready for its kind, the light follows its current light number
// (TObjEnemy::GetCurrentLightNum, slot 0x90), then its body and, when there
// is one, its last part are rendered.

class TEnemyMatTexture
{
public:
	void PreDisp(s32 kind);

	u8 unk00[0x14];
}; // 0x14

namespace nRender
{
void SetLightNum(u32 light);
}

struct RpClump;

struct CaptureBase {
	u8 unk000[0x18];
};

// TObjEnemy's virtual functions up to GetCurrentLightNum (slot 0x90).
class Capture : public CaptureBase
{
public:
	virtual ~Capture();
	virtual void Virtual0C();
	virtual void Virtual10();
	virtual void Virtual14();
	virtual void Virtual18();
	virtual void Virtual1C();
	virtual void Virtual20();
	virtual void Virtual24();
	virtual void Virtual28();
	virtual void Virtual2C();
	virtual void Virtual30();
	virtual void Virtual34();
	virtual void Virtual38();
	virtual void Virtual3C();
	virtual void Virtual40();
	virtual void Virtual44();
	virtual void Virtual48();
	virtual void Virtual4C();
	virtual void Virtual50();
	virtual void Virtual54();
	virtual void Virtual58();
	virtual void Virtual5C();
	virtual void Virtual60();
	virtual void Virtual64();
	virtual void Virtual68();
	virtual void Virtual6C();
	virtual void Virtual70();
	virtual void Virtual74();
	virtual void Virtual78();
	virtual void Virtual7C();
	virtual void Virtual80();
	virtual void Virtual84();
	virtual void Virtual88();
	virtual void Virtual8C();
	virtual u32 GetCurrentLightNum();

	u8 unk01C[0xCC];
	RpClump* body; // 0x0E8
	u8 unk0EC[0x1FC];
	RpClump* lastPart; // 0x2E8
	u8 unk2EC[0x290];
	s32 special; // 0x57C
};

extern "C" TEnemyMatTexture captureObjectGlobalArray[8];

extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void captureDispModel(Capture* object)
{
	s32 i;

	for (i = 0; i < 2; i++) {
		captureObjectGlobalArray[i].PreDisp(object->special);
	}
	nRender::SetLightNum(object->GetCurrentLightNum());
	fn_8014FF2C(object->body);
	if (object->lastPart != NULL) {
		fn_8014FF2C(object->lastPart);
	}
}
