#include "GateClock.hh"

GateClock* GateClock::Instance = 0;

GateClock::GateClock():Time(0.0)
{}

GateClock::~GateClock() 
{}

G4double GateClock::GetCurrentTimeSliceStart()
{
    for (G4int i = 0; i < FrameVector.size(); i++)
    {
        if ((!FrameVector[i+1])||((Time > FrameVector[i])&&(Time <= FrameVector[i+1])))
            return FrameVector[i];
    }
}

G4double GateClock::GetCurrentTimeSliceEnd()
{
    for (G4int i = 0; i < FrameVector.size(); i++)
    {
        if (FrameVector[i+1])
            if ((Time > FrameVector[i])&&(Time <= FrameVector[i+1]))
                return FrameVector[i+1];
            else
                return TimeEnd;
    }
}

bool GateClock::NextSlice()
{
    for (G4int i = 0; i < FrameVector.size(); i++)
    {
        if (!FrameVector[i+1])
            return 0;
        else if ((Time > FrameVector[i])&&(Time <= FrameVector[i+1]))
        {
            Time = FrameVector[i+1];
            return 1;
        }
    }
}



