// EffSpark (the PS2 build's class; its instance is EffSparkTp): the sparks
// effect, a model template and up to 512 live sparks. Shared by the EffSpark
// units. effSparkDestroy (the name is ours) frees one spark, its model and its
// RwMalloc block; it is inline here (effSparkClearAll inlines it) and has an
// out-of-line copy in rel/eff_spark_destroy.cpp, which defines
// EFF_SPARK_DESTROY_INLINE empty.

#include "game/effect/eff_bomb.h"

typedef struct RwRGBAReal {
	f32 red, green, blue, alpha;
} RwRGBAReal;

typedef struct EffSparkParticle {
	RpClump* clump;   // 0x00
	u8 unk04[0x58];
	RwRGBAReal color; // 0x5C
} EffSparkParticle;

typedef struct RwGlobals {
	u8 unk000[0x138];
	void (*rwfree)(void* p); // 0x138
} RwGlobals;

class EffSpark : public TObject
{
public:
	EffSpark(TObject* parent);
	virtual void Exec();
	virtual void TDisp();
	virtual ~EffSpark();

	RpClump* clump;                   // 0x28
	EffSparkParticle* sparks[0x200];  // 0x2C
}; // 0x82C

extern "C" EffSpark* EffSparkTp;
extern "C" char* CL_EffSpark;
extern "C" char effSparkModelName[];
extern "C" TObject* lbl_8042C110;
extern "C" void* lbl_8042C1D0;
extern "C" RwGlobals* lbl_8042C9A4;

extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_8004A774(void* resources, char* name);
extern "C" void* memset(void* dst, int value, unsigned long size);

#ifndef EFF_SPARK_DESTROY_INLINE
#define EFF_SPARK_DESTROY_INLINE inline
#endif

extern "C" EFF_SPARK_DESTROY_INLINE int effSparkDestroy(EffSpark* spark, EffSparkParticle* particle)
{
	if (particle == NULL) {
		return 0;
	}
	if (particle->clump != NULL) {
		fn_80150958(particle->clump);
		particle->clump = NULL;
	}
	lbl_8042C9A4->rwfree(particle);
	return 1;
}

