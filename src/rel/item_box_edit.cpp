#include "types.h"

// The item box's EditOnChange (itemBoxEditOnChange here): it keeps the edited
// item within 0..12 and names the editor's first two fields for the item and
// the mode. The mode's own bounds (0..1) write the item field, not the mode:
// the original's slip, kept.

typedef struct ItemBoxParams {
	s8 item; // 0x00
	s8 mode; // 0x01
} ItemBoxParams;

typedef struct ItemBoxEdit {
	u8 unk00[0x2C];        // 0x00
	ItemBoxParams* params; // 0x2C
} ItemBoxEdit;

extern "C" const char* itemBoxFieldNames[];
extern "C" const char* itemBoxItemFields[13];
extern "C" const char* itemBoxModeFields[2];

extern "C" void itemBoxEditOnChange(void* object, ItemBoxEdit* edit)
{
	ItemBoxParams* params = edit->params;

	if (params->item < 0) {
		params->item = 0;
	}
	if (params->item >= 13) {
		params->item = 12;
	}
	if (params->mode < 0) {
		params->item = 0;
	}
	if (params->mode > 1) {
		params->item = 1;
	}
	itemBoxFieldNames[0] = itemBoxItemFields[params->item];
	itemBoxFieldNames[1] = itemBoxModeFields[params->mode];
}
