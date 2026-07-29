typedef int s32;

class GetSpParam
{
public:
	GetSpParam()
	{
		for (s32 i = 0; i < 4; ++i) {
			powerGauge[i]    = 0.0f;
			path.values[i]   = 0.0f;
			button.values[i] = 0;
		}
		time.value = 0;
	}
	~GetSpParam();

	void ResetTimeExtended();
	s32 GetExtendedTime();
	void TimeExtended(s32 time);
	void SetPutBButton(s32 index, s32 value);
	s32 CheckPutBButton(s32 index);
	void SpCalcPathGauge(s32 index, float amount);
	void SpSetPathGauge(s32 index, float value);
	float SpGetPathGauge(s32 index);
	void SpSubPowerGauge(s32 index, float amount);
	void SpSetPowerGauge(s32 index, float value);
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

void GetSpParam::ResetTimeExtended()
{
	time.value = 0;
}

s32 GetSpParam::GetExtendedTime()
{
	return time.value;
}

void GetSpParam::TimeExtended(s32 time)
{
	this->time.value += time;
}

void GetSpParam::SetPutBButton(s32 index, s32 value)
{
	button.values[index] = value;
}

s32 GetSpParam::CheckPutBButton(s32 index)
{
	return button.values[index];
}

void GetSpParam::SpCalcPathGauge(s32 index, float amount)
{
	path.values[index] += amount / 100.0f;

	if (path.values[index] < 0.0f) {
		path.values[index] = 0.0f;
	} else if (path.values[index] > 1.0f) {
		path.values[index] = 1.0f;
	}
}

void GetSpParam::SpSetPathGauge(s32 index, float value)
{
	if ((value < 0.0f || value > 1.0f) && value != -1.0) {
		return;
	}
	path.values[index] = value;
}

float GetSpParam::SpGetPathGauge(s32 index)
{
	if (index < 0 || index > 4) {
		return 0.0f;
	}
	return path.values[index];
}

void GetSpParam::SpSubPowerGauge(s32 index, float amount)
{
	powerGauge[index] -= amount / 300.0f;

	if (powerGauge[index] < 0.0f) {
		powerGauge[index] = 0.0f;
	} else if (powerGauge[index] > 1.0f) {
		powerGauge[index] = 1.0f;
	}
}

void GetSpParam::SpSetPowerGauge(s32 index, float value)
{
	if (value < 0.0f || value > 1.0f) {
		return;
	}
	powerGauge[index] = value;
}

float GetSpParam::SpGetPowerGauge(s32 index)
{
	if (index < 0 || index > 4) {
		return 0.0f;
	}
	return powerGauge[index];
}

GetSpParam::~GetSpParam() { }

GetSpParam SpParam;

extern const unsigned int sGetSpParamPadding = 0;
