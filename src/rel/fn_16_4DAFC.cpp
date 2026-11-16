typedef unsigned int u32;

struct TextureEntry4DAFC {
	void* texture;    // 0x0
	const char* name; // 0x4
};

extern "C" {
void fn_801A4C84(void* dictionary);
void* fn_801A4BBC(void* dictionary, const char* name);

void fn_16_4DAFC(TextureEntry4DAFC* table, void* dictionary)
{
	int i;

	fn_801A4C84(dictionary);
	i = 0;
	while (table[i].name != 0) {
		table[i].texture = fn_801A4BBC(dictionary, table[i].name);
		i++;
	}
}
}
