// Marks the fighter's state flag 0x1000 and switches its motion (0x6F4) to 0x31,
// unless the flag is already set and the motion is already 0x3F.

extern "C" {
struct Fighter8004469C {
	unsigned char pad[0x6F4];
	short motion; // 0x6F4
	short flags;  // 0x6F6
};

void fn_8004469C(Fighter8004469C* fighter)
{
	if ((fighter->flags & 0x1000) != 0) {
		if (fighter->motion == 0x3F) {
			return;
		}
	}
	fighter->flags |= 0x1000;
	fighter->motion = 0x31;
}
}
