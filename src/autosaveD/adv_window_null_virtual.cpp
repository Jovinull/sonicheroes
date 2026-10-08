#include "types.h"

// The empty four-byte function between the ADV_WINDOW unit (adv_window.cpp,
// ending at .text 0x4070) and ADV_MENU (adv_menu.cpp, from 0x4074). Its only
// reference is a slot in the ADV_WINDOW vtable in .data (0x450), so it is an
// empty virtual this module emits on its own: the advertiseD adv_window source
// does not produce it. Which virtual it is (and so its real name) is not yet
// established; kept as a separate fragment until it is.
extern "C" void fn_2_4070(void* window) { }
