#include "types.h"

// The capture enemy's event hook (captureEvent here), the same in the seven
// stage modules that carry the capture: event 0 lets the held player go
// (mode 0xF) and destroys the enemy through its vtable (DestroyMyself),
// event 1 asks for it to be killed, events 2 and 3 do nothing.

struct CaptureBase {
	u8 unk000[0x4];
	u16 signal; // 0x004
	u8 unk006[0x12];
};

// TObjEnemy's virtual functions up to DestroyMyself (slot 0x3C).
class Capture : public CaptureBase
{
public:
	virtual ~Capture();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char* message);
	virtual void Render();
	virtual void Virtual2C();
	virtual void Virtual30();
	virtual void Virtual34();
	virtual void CheckDamage2();
	virtual void DestroyMyself();

	u8 unk01C[0x25C];
	s32 player; // 0x278
};

extern "C" void fn_800E1208(s32 player, s32 mode, s32 arg);

extern "C" void captureEvent(Capture* object, s32 event)
{
	switch (event) {
		case 0:
			if (object->player != -1) {
				fn_800E1208(object->player, 0xF, 0);
				object->player = -1;
			}
			object->DestroyMyself();
			return;
		case 1:
			object->signal |= 1;
			return;
		case 2:
		case 3:
			break;
	}
}
