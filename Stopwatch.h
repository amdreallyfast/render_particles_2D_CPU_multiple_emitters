#pragma once

// TODO: header
class Stopwatch
{
public:
    bool Init();

    // delta time is in seconds
    void Start();
    double Lap();
    double TotalTime();
    void Reset();
};

