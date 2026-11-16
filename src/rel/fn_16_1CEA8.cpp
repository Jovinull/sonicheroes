extern "C" int fn_16_331C(unsigned char);
extern "C" int fn_16_1CEA8(register char* obj)
{
	if (obj[0xB8] == 0 || obj[0xB8] == 1 || obj[0xB8] == 2) {
		return 0;
	}
	if (fn_16_331C(*(unsigned char*)(obj + 0xB9)) != 0) {
		return 1;
	}
	return 0;
}
