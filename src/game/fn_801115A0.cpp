// Draws an object's caption with a drop shadow (HYPOTHESIS; names inferred): unless captions are
// off (0x20 of lbl_8042C180) or the object has no text (0x2C), saves the blend, z-test, texture
// address and shade render states, draws the text once offset by lbl_8042E960 in shadow blending
// and once in place in additive blending with the object's message window (0x7C) or the shared
// MessageEuc, then restores the states. Built with the game-unit flags (-opt noschedule,
// nopeephole).
// NonMatching: retail loads the call arguments in order and the shadow offset after the y
// position, while this source loads the offset first (20 words, same instructions). Const
// constants do not change the order.
#include "types.h"

enum Rt2dJustificationType { rt2dJUSTIFYLEFT, rt2dJUSTIFYCENTER, rt2dJUSTIFYRIGHT };

// Declaration of the message window class used here (its own unit defines it).
class MESSAGE
{
public:
	void DisplayMessage(
	    char* text, float x, float y, Rt2dJustificationType justify, float a, float b);
};

struct Mode801115A0 {
	u8 pad0[0x20];
	s8 captionsOff; // 0x20
};

struct Caption801115A0 {
	u8 pad0[0x2C];
	char* text; // 0x2C
	u8 pad30[0x7C - 0x30];
	MESSAGE* message; // 0x7C
};

extern MESSAGE* MessageEuc;

extern "C" {
extern Mode801115A0* lbl_8042C180;
extern f32 lbl_8042B7E8;
extern f32 lbl_8042B7EC;
extern f32 lbl_8042E960;
extern f32 lbl_8042E964;
// HYPOTHESIS: RwRenderStateGet and RwRenderStateSet.
s32 fn_80194294(s32 state, void* value);
s32 fn_80194234(s32 state, void* value);

void fn_801115A0(Caption801115A0* caption)
{
	void* srcBlend;
	void* destBlend;
	void* zTest;
	void* textureAddress;
	void* shadeMode;

	if (lbl_8042C180->captionsOff == 0 && caption->text != 0) {
		fn_80194294(10, &srcBlend);
		fn_80194294(11, &destBlend);
		fn_80194294(20, &zTest);
		fn_80194234(20, (void*)1);
		fn_80194294(2, &textureAddress);
		fn_80194294(9, &shadeMode);
		fn_80194234(2, (void*)3);
		fn_80194234(10, (void*)1);
		fn_80194234(11, (void*)4);
		if (caption->message != 0) {
			caption->message->DisplayMessage(caption->text, lbl_8042B7E8,
			    lbl_8042B7EC - lbl_8042E960, rt2dJUSTIFYCENTER, lbl_8042E960, lbl_8042E964);
		} else {
			MessageEuc->DisplayMessage(caption->text, lbl_8042B7E8, lbl_8042B7EC - lbl_8042E960,
			    rt2dJUSTIFYCENTER, lbl_8042E960, lbl_8042E964);
		}
		fn_80194234(10, (void*)5);
		fn_80194234(11, (void*)4);
		fn_80194234(9, (void*)1);
		if (caption->message != 0) {
			caption->message->DisplayMessage(caption->text, lbl_8042B7E8, lbl_8042B7EC,
			    rt2dJUSTIFYCENTER, lbl_8042E964, lbl_8042E964);
		} else {
			MessageEuc->DisplayMessage(caption->text, lbl_8042B7E8, lbl_8042B7EC, rt2dJUSTIFYCENTER,
			    lbl_8042E964, lbl_8042E964);
		}
		fn_80194234(9, shadeMode);
		fn_80194234(2, textureAddress);
		fn_80194234(20, zTest);
		fn_80194234(10, srcBlend);
		fn_80194234(11, destBlend);
	}
}
}
