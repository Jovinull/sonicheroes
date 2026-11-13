typedef int s32;
typedef float f32;

class GetSpParam
{
public:
	float SpGetPowerGauge(s32 index);

private:
	union {
		float powerGauge[9];
		struct {
			char padding[8];
			float values[7];
		} path;
		struct {
			char padding[20];
			s32 values[4];
		} button;
		struct {
			char padding[28];
			s32 value;
		} time;
	};
};

extern GetSpParam SpParam;

struct UnkObj80137150 {
	char pad[0x40];
	f32 field_40;
	s32 field_44;
};

extern "C" void fn_80137150(UnkObj80137150* arg0)
{
	arg0->field_40 = SpParam.SpGetPowerGauge(arg0->field_44);
}
