extern "C" {
struct Obj800AB35C {
	unsigned char pad[0x6F0];
	signed short state; // 0x6F0
	signed short pad2;
	signed short unk6F4; // 0x6F4
	signed short flags;  // 0x6F6
};

int fn_800AB35C(Obj800AB35C* obj)
{
	switch (obj->state) {
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x21:
		case 0x29:
		case 0x2A:
		case 0x2B:
		case 0x2C:
		case 0x33:
		case 0x53:
			if (!(obj->unk6F4 == 0xF && (obj->flags & 0x1000))) {
				return 1;
			}
			break;
	}
	return 0;
}
}
