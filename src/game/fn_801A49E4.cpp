// Copies at most 32 characters of name into the texture's name (HYPOTHESIS: RwTextureSetName). A name
// of 32 characters or more records core error 0x8000001E (string truncated, with the name, the
// limit and the last kept character) and is cut to 31 characters. Returns the texture.
#include "game/rw_engine.h"

#define RW_TEXTURE_BASE_NAME_LENGTH 32
#define RW_ERROR_STRING_TRUNCATED   ((s32)0x8000001E)

extern "C" {
RwTexture* fn_801A49E4(RwTexture* texture, const char* name)
{
	lbl_8042C9A4->rwstrncpy(texture->name, name, RW_TEXTURE_BASE_NAME_LENGTH);
	if (lbl_8042C9A4->rwstrlen(name) >= RW_TEXTURE_BASE_NAME_LENGTH) {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(RW_ERROR_STRING_TRUNCATED, name, RW_TEXTURE_BASE_NAME_LENGTH,
		    RW_TEXTURE_BASE_NAME_LENGTH - 1, name[RW_TEXTURE_BASE_NAME_LENGTH - 1]);
		fn_80193FE8(&error);
		texture->name[RW_TEXTURE_BASE_NAME_LENGTH - 1] = 0;
	}
	return texture;
}
}
