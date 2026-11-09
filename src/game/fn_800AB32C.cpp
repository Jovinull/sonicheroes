// Whether the object is in state 9 and has its flag byte at 0x6A0 set.

extern "C" {
struct Obj800AB32C {
	unsigned char pad[0x6A0];
	signed char flag; // 0x6A0
	unsigned char pad2[0xC0];
	signed char state; // 0x761
};

int fn_800AB32C(Obj800AB32C* obj)
{
	if (obj->state != 9) {
		return 0;
	}
	return obj->flag != 0;
}
}
