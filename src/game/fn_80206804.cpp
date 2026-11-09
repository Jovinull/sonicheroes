// 0 when the object is there and its key (0x04) is the one stored in the
// current stage block, 1 otherwise.

extern "C" {
extern unsigned char* lbl_8042CF6C;
struct Obj80206804 {
	int unk0;
	unsigned int key; // 0x04
};

int fn_80206804(Obj80206804* obj)
{
	if (obj != 0 && obj->key == *(unsigned int*)(lbl_8042CF6C + 0x10000 - 0x204)) {
		return 0;
	}
	return 1;
}
}
