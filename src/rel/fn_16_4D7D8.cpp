typedef unsigned int u32;

struct ClumpEntry40D {
	void* clump;
	char* filename;
};

extern "C" {
void fn_80150958(void* clump);

void fn_16_4D7D8(ClumpEntry40D* table)
{
	int i;

	for (i = 0; table[i].filename != 0; i++) {
		if (table[i].clump != 0) {
			fn_80150958(table[i].clump);
			table[i].clump = 0;
		}
	}
}
}
