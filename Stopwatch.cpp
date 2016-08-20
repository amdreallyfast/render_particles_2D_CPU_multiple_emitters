#include "Stopwatch.h"

// this is a big header, but necessary to get access to LARGE_INTEGER
// Note: We can't just include winnt.h, in which LARGE_INTEGER is defined, because there are some macros that this header file needs that are defined further up in the header hierarchy.  So just include Windows.h and be done with it.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// these are declared static here in order to avoid having to include Windows.h in the header
static double gInverseCpuTimerFrequency;
static LARGE_INTEGER gStartCounter;
static LARGE_INTEGER gLastLapCounter;

// TODO: header
static inline double CounterToSeconds(const LARGE_INTEGER counter)
{
    return ((double)counter.QuadPart * gInverseCpuTimerFrequency);
}

// TODO: header
bool Stopwatch::Init()
{
    // the "performance frequency" only changes on system reset, so it's ok to set it only during initialization
    // Note: If it succeeds, it returns non-zero, not a bool as C++ knows it.  Rather, it returns a BOOL (typedef of an int).
    // http://msdn.microsoft.com/en-us/library/windows/desktop/ms644905(v=vs.85).aspx
    LARGE_INTEGER cpuFreq;
    bool success = (0 != QueryPerformanceFrequency(&cpuFreq));
    gInverseCpuTimerFrequency = 1.0 / cpuFreq.QuadPart;

    return success;
}

void Stopwatch::Start()
{
    // give the counters their first values
    // Note: "On systems that run Windows XP or later, the function will always succeed and will thus never return zero."
    // http://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx
    QueryPerformanceCounter(&gStartCounter);
    gLastLapCounter.QuadPart = gStartCounter.QuadPart;
}

double Stopwatch::Lap()
{
    // get the current time
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    // calculate delta time relative to previous frame
    LARGE_INTEGER delta_large_int;
    delta_large_int.QuadPart = now.QuadPart - gLastLapCounter.QuadPart;
    double delta_time = CounterToSeconds(delta_large_int);

    gLastLapCounter.QuadPart = now.QuadPart;

    return delta_time;
}

double Stopwatch::TotalTime()
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    double delta_time = CounterToSeconds(now);
    return delta_time;
}

void Stopwatch::Reset()
{
    // reset the values by giving them new start values
    Start();
}
