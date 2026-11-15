// Refreshes an object's path gauges from the special-move parameters (HYPOTHESIS; the owner type
// is UNKNOWN): when fn_80018EA8 reports the record at lbl_8029C310 ready, stores path gauge 0 of
// SpParam at 0x28 and, when the flag at 0x1E of the object at lbl_8042C180 is set, path gauge 1
// at 0x2C (otherwise the .sdata2 default lbl_8042EC30).
#include "types.h"

// Declaration of the special-move parameter table used here (defined in GetSpParam.cpp).
// Only the method used here is declared; the size keeps the object out of small data.
class GetSpParam
{
public:
	float SpGetPathGauge(s32 index);

private:
	u8 data[0x24]; // UNKNOWN layout (SpParam is 0x24 bytes)
};

struct Gauges80120144 {
	u8 pad0[0x28];
	f32 gauge0; // 0x28
	f32 gauge1; // 0x2C
};

struct Mode80120144 {
	u8 pad0[0x1E];
	s8 hasSecondPath; // 0x1E
};

extern GetSpParam SpParam;

extern "C" {
extern u8 lbl_8029C310[];
extern Mode80120144* lbl_8042C180;
extern f32 lbl_8042EC30;
s32 fn_80018EA8(void* record);

void fn_80120144(Gauges80120144* gauges)
{
	if (fn_80018EA8(lbl_8029C310)) {
		gauges->gauge0 = SpParam.SpGetPathGauge(0);
		if (lbl_8042C180->hasSecondPath) {
			gauges->gauge1 = SpParam.SpGetPathGauge(1);
		} else {
			gauges->gauge1 = lbl_8042EC30;
		}
	}
}
}
