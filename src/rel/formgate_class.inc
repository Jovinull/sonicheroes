#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjFormGate (the PS2 build's class): the formation gate. SetParameter is
// inline here and also has an out-of-line copy (rel/formgate_set_parameter.cpp,
// which defines FORMGATE_SET_PARAMETER_INLINE empty).

struct FormGateParams {
	s8 kind;     // 0x00
	u8 pad01[0x3];
	f32 width;   // 0x04
	f32 height;  // 0x08
};

class TObjFormGate : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 state;          // 0xB8
	s8 kind;            // 0xBC
	u8 padBD[0x3];
	RwV3d pos;          // 0xC0
	RwV3d startPos;     // 0xCC
	sAngle ang;         // 0xD8
	f32 width;          // 0xE4
	f32 height;         // 0xE8
	RpClump* models[3]; // 0xEC

	TObjFormGate(TObject* parent);
	// TDisp comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void TDisp();
	virtual void Exec();
	virtual void Disp();
	virtual ~TObjFormGate();
	virtual void EditOnChange(SETDATA_PARAM* param);
	void SetPosition();
	void SetParameter();
}; // 0xF8

extern "C" const f32 formgateWidthScale[1];

#ifndef FORMGATE_SET_PARAMETER_INLINE
#define FORMGATE_SET_PARAMETER_INLINE inline
#endif

// The placement: position (also kept as the start), angles, kind and the
// gate's size.
FORMGATE_SET_PARAMETER_INLINE void TObjFormGate::SetParameter()
{
	FormGateParams* params = (FormGateParams*)ObjParam->setData.setBuffer;

	pos      = ObjParam->setData.pos;
	startPos = pos;
	ang      = ObjParam->setData.ang;
	kind     = params->kind;
	width    = formgateWidthScale[0] * params->width;
	height   = params->height;
}
