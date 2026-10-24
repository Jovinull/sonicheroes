#include "types.h"

// The train's Unload and Load hooks (traintrainUnload and traintrainLoad
// here). The Unload releases the nine models and the animations of the current
// animation table, then forgets the table. The Load makes the module's texture
// dictionary current, reads the module's model archive and loads the nine
// models each from its own archive; it then picks the animation table for the
// current stage (stage 7 has two, chosen by the player state's 0x28 byte),
// loads each table entry's animation and keeps its length, and resets the 32
// train-car slots.

// one of the train's models: its archive and file name, and the model once
// loaded
typedef struct TraintrainModel {
	void* archive;    // 0x00
	const char* name; // 0x04
	u8 unk08[0x4];
	void* model; // 0x0C
	u8 unk10[0x8];
} TraintrainModel; // 0x18

// one entry of an animation table: its archive and file name, the animation's
// length and the animation once loaded (a null archive ends the table)
typedef struct TraintrainAnimation {
	void* archive;    // 0x00
	const char* name; // 0x04
	u8 unk08[0x4];
	f32 duration; // 0x0C
	u8 unk10[0x4];
	void* animation; // 0x14
	u8 unk18[0x4];
} TraintrainAnimation; // 0x1C

// one train-car slot
typedef struct TraintrainCar {
	s32 state;   // 0x00
	f32 speed;   // 0x04
	s32 counter; // 0x08
	u8 unk0C[0x14];
} TraintrainCar; // 0x20

// the game state (only the stage record is read here)
typedef struct TraintrainGameState {
	u8 unk00[0x34];
	s32* stage; // 0x34: the stage id is its second word
} TraintrainGameState;

extern "C" TraintrainGameState lbl_8029C310;
extern "C" u8* lbl_8042C180;
extern "C" TraintrainModel traintrainModels[9];
extern "C" TraintrainAnimation* traintrainAnimations;
extern "C" s32 traintrainAnimationCount;
extern "C" TraintrainCar traintrainCars[32];
extern "C" const f32 lbl_6_rodata_156C;
extern "C" TraintrainAnimation lbl_6_data_F1E8[];
extern "C" TraintrainAnimation lbl_6_data_F4C4[];
extern "C" TraintrainAnimation lbl_6_data_F8E0[];
extern "C" TraintrainAnimation lbl_6_data_FA74[];
extern "C" TraintrainAnimation lbl_6_data_FBA4[];
extern "C" TraintrainAnimation lbl_6_data_FC30[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void traintrainUnload(void)
{
	s32 i;

	for (i = 0; i < 9; i++) {
		fn_80150958(traintrainModels[i].model);
	}
	for (i = 0; i < traintrainAnimationCount; i++) {
		if (traintrainAnimations[i].animation != NULL) {
			fn_8020C2D8(traintrainAnimations[i].animation);
		}
	}
	traintrainAnimations = NULL;
}

extern "C" void traintrainLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (s32 i = 0; i < 9; i++) {
		traintrainModels[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), traintrainModels[i].name),
		    traintrainModels[i].archive);
	}
	switch (lbl_8029C310.stage[1]) {
		case 7:
			if ((s8)lbl_8042C180[0x28] == 2) {
				traintrainAnimations = lbl_6_data_F4C4;
			} else {
				traintrainAnimations = lbl_6_data_F1E8;
			}
			break;
		case 8:
			traintrainAnimations = lbl_6_data_F8E0;
			break;
		case 0x32:
			traintrainAnimations = lbl_6_data_FA74;
			break;
		case 0x46:
			traintrainAnimations = lbl_6_data_FBA4;
			break;
		case 0x48:
			traintrainAnimations = lbl_6_data_FC30;
			break;
	}
	for (traintrainAnimationCount = 0;
	    traintrainAnimations[traintrainAnimationCount].archive != NULL;
	    traintrainAnimationCount++) {
		TraintrainAnimation* entry = &traintrainAnimations[traintrainAnimationCount];

		if (entry->name != NULL) {
			entry->animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), entry->name),
			    entry->archive);
			entry->duration  = *(f32*)((u8*)entry->animation + 0xC);
		}
	}
	for (s32 i = 0; i < 32; i++) {
		traintrainCars[i].speed   = lbl_6_rodata_156C;
		traintrainCars[i].counter = 13;
		traintrainCars[i].state   = 0;
	}
}
