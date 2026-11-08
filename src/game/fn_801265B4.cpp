// How an entry is filled: 0 with no first word, 2 with a first word but no
// second one, 1 with both.

extern "C" {
struct Obj801265B4 {
	unsigned char pad[8];
	unsigned int first;  // 0x08
	unsigned int second; // 0x0C
};

int fn_801265B4(Obj801265B4* obj)
{
	if (obj->first == 0) {
		return 0;
	}
	if (obj->second == 0) {
		return 2;
	}
	return 1;
}
}
