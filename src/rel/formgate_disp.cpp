#include "types.h"

// TObjFormGate::Disp (the PS2 build's name). With the game not paused and the
// gate in the camera's view, it lights the gate by the placement's light bits,
// shows the gate's sign for its kind on the sign effect's first layer and one
// of the arrow textures by the stage timer (four frames) on the second (or
// puts the sign on the gate's material when there is no effect), gives the
// three beam materials the glow texture picked from the timer (a sine wave
// over three frames) and draws the gate.

#include "src/rel/formgate_class.inc"

typedef struct RwSphere {
	RwV3d center; // 0x00
	f32 radius;   // 0x0C
} RwSphere;

typedef struct RwTexture RwTexture;
typedef struct RpMaterial RpMaterial;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" u8* lbl_8042C180;
extern "C" void** lbl_8042C9A4;
extern "C" CLIGHT lbl_802D5E80;
extern "C" RwTexture* formgateObjectTexture0;
extern "C" RwTexture* formgateObjectTexture1;
extern "C" RwTexture* formgateObjectTexture2;
extern "C" RwTexture* formgateObjectTexture3;
extern "C" RwTexture* formgateObjectTexture4;
extern "C" RwTexture* formgateObjectTexture5;
extern "C" RwTexture* formgateObjectTexture6;
extern "C" RwTexture* formgateObjectTexture7;
extern "C" RwTexture* formgateObjectTexture8;
extern "C" RpMaterial* formgateObjectMaterial;
extern "C" RpMaterial* formgateObjectMaterials[3];
extern "C" const f32 formgateMaxWidth[1];
extern "C" const f32 formgateBlinkScale[1];

extern "C" s32 fn_8019CE34(void* camera, RwSphere* sphere);
extern "C" void* fn_80146BC8(RpMaterial* material, s32 kind);
extern "C" void fn_80146920(void* effect, s32 layer, RwTexture* texture);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_8015498C(RpMaterial* material, RwTexture* texture);
extern "C" void fn_8014FF2C(RpClump* clump);

void TObjFormGate::Disp()
{
	u8* game = lbl_8042C180;

	if ((s8)game[0x20] == 0) {
		s32 timer = *(s32*)(game + 0x30);
		RwSphere sphere;

		sphere.center = pos;
		sphere.radius = formgateMaxWidth[0];
		if (fn_8019CE34(*lbl_8042C9A4, &sphere)) {
			RwTexture* texture;
			void* effect;

			lbl_802D5E80.SetCurrentNum(((ObjParam->setData.condition.Flag & 0x1C0000) >> 18) + 4);
			lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
			switch (kind) {
				case 0:
					texture = formgateObjectTexture0;
					break;
				case 1:
					texture = formgateObjectTexture1;
					break;
				case 2:
				default:
					texture = formgateObjectTexture2;
					break;
			}
			effect = fn_80146BC8(formgateObjectMaterial, 6);
			if (effect != NULL) {
				fn_80146920(effect, 1, texture);
				switch (*(s32*)(lbl_8042C180 + 0x30) & 3) {
					case 0:
						texture = formgateObjectTexture3;
						break;
					case 2:
						texture = formgateObjectTexture4;
						break;
					case 1:
					case 3:
						texture = formgateObjectTexture5;
						break;
				}
				fn_80146920(effect, 0, texture);
			} else {
				fn_8015498C(formgateObjectMaterial, texture);
			}

			f32 wave  = fn_800D7B00((timer << 11) % 0x10000);
			u32 frame = formgateBlinkScale[0] + formgateBlinkScale[0] * wave;

			switch ((s32)(frame >> 1)) {
				case 0:
					texture = formgateObjectTexture6;
					break;
				case 1:
					texture = formgateObjectTexture8;
					break;
				default:
					texture = formgateObjectTexture7;
					break;
			}
			for (int i = 0; i < 3; i++) {
				fn_8015498C(formgateObjectMaterials[i], texture);
			}
			fn_8014FF2C(models[0]);
		}
	}
}
