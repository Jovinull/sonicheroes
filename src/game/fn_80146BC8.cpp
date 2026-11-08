// Reads a word out of an object at the offset an entry of the table at
// lbl_803EC3F8 names, when the entry is in use; 0 otherwise. The entries are 16
// bytes.

extern "C" {
struct Entry80146BC8 {
	int unk0;
	unsigned int present; // 0x04
	int offset;           // 0x08
	int unkC;
};
extern Entry80146BC8 lbl_803EC3F8[];

int fn_80146BC8(char* object, int index)
{
	if (lbl_803EC3F8[index].present != 0) {
		return *(int*)(object + lbl_803EC3F8[index].offset);
	}
	return 0;
}
}
