#include "GateClock.hh"

GateClock* GateClock::Instance = 0;

bool GateClock::NextSlice()
{
    if (TimeIterator != FrameVector.end())
    {
        TimeIterator++;
        return 1;
    }
    else
        return 0;
}



