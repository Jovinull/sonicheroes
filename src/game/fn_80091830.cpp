// Formation/state setter for a team member object. The mode at +0x140 maps to a
// formation id (0..2); if the requested formation differs and the object is not
// mid-transition (state +0x154 in 1..3), the next form is queued at +0x150.
struct Obj80091830 {
	unsigned char pad0[0x140];
	unsigned int mode; // 0x140
	unsigned char pad144[0x150 - 0x144];
	int form;  // 0x150
	int state; // 0x154
};

extern "C" void fn_80091830(Obj80091830* object, int type)
{
	if ((unsigned int)type > 2) {
		return;
	}
	int cur;
	switch (object->mode) {
		case 0:
		case 4:
		case 7:
		case 10:
			cur = 0;
			break;
		case 1:
		case 5:
		case 6:
		case 8:
		case 11:
			cur = 1;
			break;
		case 2:
		case 3:
		case 9:
		case 12:
			cur = 2;
			break;
		default:
			return;
	}
	if (cur == type) {
		return;
	}
	if (object->state < 4) {
		if (object->state >= 1) {
			return;
		}
	}
	if ((cur == 0 && type == 2) || (cur == 2 && type == 1) || (cur == 1 && type == 0)) {
		object->form = 6;
	} else {
		object->form = 7;
	}
}
