// EventScript::dispEventMessage (the PS2 build's name): while a subtitle is up
// it draws it twice on the script's message board (the default one when the
// script has none), its shadow offset and then the text over it, with the
// blending the text wants, and puts the three render states back. This is the
// out-of-line copy nothing calls (ScriptExec has its own). The unit is built
// with -pool off so the four position literals sit in its .rodata; ScriptExec,
// left in the module's assembly, reads them by name, so
// tools/fix_stage11_symbols.py gives them the names the modules use.

#define EVENT_SCRIPT_SOURCE

#include "src/rel/event_manager_class.inc"

extern "C" void fn_80194294(s32 state, u32* value);
extern "C" void fn_80194234(s32 state, u32 value);

void EventScript::dispEventMessage()
{
	if (unk48 > 0 && messageText != NULL) {
		u32 srcBlend;
		u32 destBlend;
		u32 zTest;

		fn_80194294(10, &srcBlend);
		fn_80194294(11, &destBlend);
		fn_80194294(20, &zTest);
		fn_80194234(20, 1);
		fn_80194234(2, 3);
		fn_80194234(10, 1);
		fn_80194234(11, 4);
		if (message != NULL) {
			message->DisplayMessage(
			    messageText, 0.005f, 0.155f, (Rt2dJustificationType)1, 0.0f, 0.0f);
		} else {
			MessageEuc->DisplayMessage(
			    messageText, 0.005f, 0.155f, (Rt2dJustificationType)1, 0.0f, 0.0f);
		}
		fn_80194234(10, 5);
		fn_80194234(11, 4);
		if (message != NULL) {
			message->DisplayMessage(messageText, 0.0f, 0.16f, (Rt2dJustificationType)1, 0.0f, 0.0f);
		} else {
			MessageEuc->DisplayMessage(
			    messageText, 0.0f, 0.16f, (Rt2dJustificationType)1, 0.0f, 0.0f);
		}
		fn_80194234(10, srcBlend);
		fn_80194234(11, destBlend);
		fn_80194234(20, zTest);
	}
}
