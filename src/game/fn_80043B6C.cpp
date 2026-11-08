// Marks the fighter's state flag 0x1000 and switches its motion (0x6F4) to 0x3A,
// unless the flag is already set and the motion is already 0x3F.

extern "C" {
struct Fighter80043B6C {
	unsigned char pad[0x6F4];
	short motion; // 0x6F4
	short flags;  // 0x6F6
};

void fn_80043B6C(Fighter80043B6C* fighter)
{
	if ((fighter->flags & 0x1000) != 0) {
		if (fighter->motion == 0x3F) {
			return;
		}
	}
	fighter->flags |= 0x1000;
	fighter->motion = 0x3A;
}
}
