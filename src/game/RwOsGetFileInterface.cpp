// Returns the address of the file-interface table at +0xC4 of lbl_8042C9A4.

extern "C" {
extern int lbl_8042C9A4;

int RwOsGetFileInterface(void)
{
	return lbl_8042C9A4 + 0xc4;
}
}
