// Creates an object from a stream: gets a fresh one (fn_80171620), reads a 16-byte header from src
// (fn_801979AC) and byte-swaps it (fn_80193270); when the first word is 1 the object is filled by
// fn_80171BFC. A short read fails; a header of another version keeps the fresh object. On failure
// the fresh object is released (fn_80170FDC). Returns the object or null.
extern "C" {
void* fn_80171620(void);
unsigned int fn_801979AC(void* src, void* dst, unsigned int n);
void* fn_80193270(void* mem, unsigned int size);
void* fn_80171BFC(void* obj, int* header, void* src);
void fn_80170FDC(void* obj);

void* fn_80171E0C(void* src)
{
	void* result;
	void* obj;
	int header[4];
	obj    = fn_80171620();
	result = obj;
	if (fn_801979AC(src, header, 0x10) != 0x10) {
		result = 0;
	} else {
		fn_80193270(header, 0x10);
		switch (header[0]) {
			case 1:
				result = fn_80171BFC(obj, header, src);
				break;
		}
	}
	if (result == 0) {
		fn_80170FDC(obj);
	}
	return result;
}
}
