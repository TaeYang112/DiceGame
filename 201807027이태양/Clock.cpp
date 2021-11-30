#include "Clock.h"

Clock* Clock::Instance = nullptr;
Clock::Clock()
{
	min = 0;
	hour = 0;
	sec = 0;
    TimeSema = CreateSemaphore(NULL, 1, 1, NULL);
    TimerHandle = NULL;
}


DWORD WINAPI Clock::Timer(LPVOID Param)
{
    while (1)
    {
        Sleep(1000);
        Clock::GetInstance()->AddTime();
    }
    return 0;
}

void Clock::AddTime()
{
    WaitForSingleObject(TimeSema, INFINITE);
    sec++;
    if (sec >= 60)
    {
        sec = 0;
        min++;
        if (min >= 60)
        {
            min = 0;
            hour++;
        }
    }
    ReleaseSemaphore(TimeSema, 1, NULL);
}

Clock* Clock::GetInstance()
{
    if (!Instance)
    {
        Instance = new Clock();
    }
    return Instance;
}
void Clock::DestroyInst()
{
    if (Instance)
    {
        delete Instance;
    }
}

int Clock::GetTime(TIME time)
{
    int result = 0;
    WaitForSingleObject(TimeSema, INFINITE);
    switch (time)
    {
    case TIME::HOUR:
        result = hour;
        break;
    case TIME::MINUTE:
        result = min;
        break;
    case TIME::SECOND:
        result = sec;
        break;
    default:
        break;
    }
    ReleaseSemaphore(TimeSema, 1, NULL);
    return result;
}

void Clock::ClockClear()
{
    WaitForSingleObject(TimeSema, INFINITE);
    hour = 0;
    min = 0;
    sec = 0;
    ReleaseSemaphore(TimeSema, 1, NULL);
}

void Clock::ClockStart()
{
    if(TimerHandle == NULL)
        TimerHandle = CreateThread(NULL, 0, Timer, NULL, 0, NULL);
}

void Clock::ClockStop()
{
    if (TimerHandle != NULL)
    {
        SuspendThread(TimerHandle);
        TimerHandle = NULL;
    }
}