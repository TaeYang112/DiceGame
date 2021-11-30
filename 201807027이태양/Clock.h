#pragma once
#include "framework.h"
enum class TIME
{
	HOUR,
	MINUTE,
	SECOND
};
class Clock
{
private:
	Clock();
	~Clock() {};
	static Clock* Instance;

	int hour;
	int min;
	int sec;

	HANDLE TimeSema;
	HANDLE TimerHandle;

	static DWORD WINAPI Timer(LPVOID Param);
	void AddTime();
public:
	static Clock* GetInstance();
	static void DestroyInst();
	int GetTime(TIME time);
	void ClockClear();
	void ClockStart();
	void ClockStop();
};

