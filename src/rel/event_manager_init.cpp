// InitEventManager, the PS2 build's name for the function that sets up a
// stage's event playback: the same 97 instructions in the thirteen stage
// modules that share the engine core, at a different address and under a
// different placeholder name in each, so each module's splits.txt names its
// own range and its symbols.txt gives it this name.
//
// It creates the EventManager under the task at lbl_8042C104 and the
// EventScript, keeping them in what the PS2 build calls EventManagerTp and
// EventScriptTp (lbl_8042C6E4 and lbl_8042C6E0 here), and returns whether the
// manager exists. Both allocations are real new-expressions; the manager's
// constructor and Init are inlined, the script's constructor is not.
//
// Init gives the manager a 256 KiB buffer and a ONEFILE reading into it, then
// clears its state, the fourteen scene slots (each marked free with -1) and
// the sixteen entries after them. The slot is reached through a local pointer
// and the two loops have their own counters, which is how the original
// spreads them over five saved registers.

#include "src/rel/event_manager_class.inc"

s32 InitEventManager()
{
	lbl_8042C6E4 = new EventManager(lbl_8042C104);
	lbl_8042C6E0 = new EventScript();
	return lbl_8042C6E4 != NULL;
}
