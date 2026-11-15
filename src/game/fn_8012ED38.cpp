// Loads the text table of the current language (HYPOTHESIS; names inferred) on the first of
// paired calls (lbl_8042C768 counts the users; fn_8012ECE0 releases it): reads the file named by
// lbl_8028AE48[language] (fn_800426E0) into lbl_8042C76C and relocates it in place. The file holds
// a group count, the string count of each group, then the offset of every string; each group count
// becomes a pointer to the group's first string slot and each offset a string pointer, and the
// group table goes to lbl_8042C770 (read by fn_8012ECA8).
// NonMatching: retail keeps the string total in the register of the second loop counter; this
// draft copies it there with one extra mr (declaration orders and loop shapes tried).
#include "types.h"

struct MainState8012ED38 {
	u8 pad0[0x13];
	s8 language; // 0x13
};

extern "C" {
extern s32 lbl_8042C768;
extern s32* lbl_8042C76C;
extern char*** lbl_8042C770;
extern MainState8012ED38* lbl_8042C180;
extern char* lbl_8028AE48[];
void* fn_800426E0(const char* name, s32* size);

void fn_8012ED38(void)
{
	s32 size;
	s32 count;
	s32 total;
	s32* data;
	char** strings;
	s32* entry;
	s32* groups;

	if (lbl_8042C768 == 0) {
		data         = (s32*)fn_800426E0(lbl_8028AE48[lbl_8042C180->language], &size);
		lbl_8042C76C = data;
		count        = data[0];
		strings      = (char**)(data + (count + 1));
		entry        = data + 1;
		total        = 0;
		groups       = entry;
		for (; count > 0; count--) {
			s32 n = *entry;
			total += n;
			*(char***)entry = strings;
			strings += n;
			entry++;
		}
		for (; total > 0; total--) {
			*entry += (s32)data;
			entry++;
		}
		lbl_8042C770 = (char***)groups;
	}
	lbl_8042C768++;
}
}
