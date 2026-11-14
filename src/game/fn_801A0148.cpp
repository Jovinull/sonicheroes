// Search-path callback handed to fn_8019FE30 by the image readers around 0x801A0300: when the
// candidate file exists it runs the context's reader on it and stores the result. Returns 0 to
// stop the search once a reader succeeded, otherwise the candidate name to continue
// (HYPOTHESIS: RenderWare image path search callback).
#include "game/rw_engine.h"

// Search context built on the caller's stack (field names inferred from this use).
struct RwImagePathSearch {
	void* (*read)(const char* name); // 0x0
	void* result;                    // 0x4
};

extern "C" {
const char* fn_801A0148(const char* name, RwImagePathSearch* search)
{
	if (lbl_8042C9A4->rwfexist(name)) {
		search->result = search->read(name);
		if (search->result) {
			return 0;
		}
	}
	return name;
}
}
