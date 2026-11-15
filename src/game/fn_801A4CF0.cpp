// Reads a texture by name (HYPOTHESIS: RwTextureRead): a texture the find callback already knows
// gains a reference; otherwise the read callback loads it, and a failure raises error 0x16 of
// plugin 1 with the name and mask (or "(null)"). A loaded texture is added to the current texture
// dictionary, leaving any dictionary it was in. Returns the texture, or null.
#include "game/rw_frame.h"

typedef RwTexture* (*RwTextureCallBackRead801A4CF0)(const char* name, const char* maskName);
typedef RwTexture* (*RwTextureCallBackFind801A4CF0)(const char* name, const char* maskName);

// Texture module callbacks (HYPOTHESIS: textureReadCallBack at +0x14, textureFindCallBack at +0x18).
#define RW_TEXTURE_READ_CALLBACK (*(RwTextureCallBackRead801A4CF0*)(RW_TEXTURE_GLOBALS + 0x14))
#define RW_TEXTURE_FIND_CALLBACK (*(RwTextureCallBackFind801A4CF0*)(RW_TEXTURE_GLOBALS + 0x18))

#define RW_ERROR_READ_TEXTURE_801A4CF0 0x16

extern "C" {
extern char lbl_8042BE44[7]; // "(null)" (.sdata)

RwTexture* fn_801A4CF0(const char* name, const char* maskName)
{
	RwTexture* texture;
	RwTexDictionary* dict;

	texture = RW_TEXTURE_FIND_CALLBACK(name, maskName);
	if (texture != 0) {
		texture->refCount++;
		return texture;
	}

	texture = RW_TEXTURE_READ_CALLBACK(name, maskName);
	if (texture == 0) {
		if (maskName != 0) {
			RwError error;
			error.pluginID  = 1;
			error.errorCode = fn_8019408C(RW_ERROR_READ_TEXTURE_801A4CF0, name, maskName);
			fn_80193FE8(&error);
		} else {
			RwError error;
			error.pluginID  = 1;
			error.errorCode = fn_8019408C(RW_ERROR_READ_TEXTURE_801A4CF0, name, lbl_8042BE44);
			fn_80193FE8(&error);
		}
		return 0;
	}

	dict = RW_CURRENT_TEX_DICTIONARY;
	if (dict != 0) {
		if (texture->dict != 0) {
			RwLLLinkRemove(&texture->lInDictionary);
		}
		texture->dict = dict;
		RwLinkListAddLLLink(&dict->texturesInDict, &texture->lInDictionary);
	}
	return texture;
}
}
