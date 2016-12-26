#include "GateClock.hh"

GateClock* GateClock::Instance = 0;

GateClock::GateClock():Time(0.0)
{}

GateClock::~GateClock() 
{}

G4double GateClock::GetCurrentTimeSliceStart()
{
    for (G4int i = 0; i < TimeSlices.size(); i++)
    {
        if ((!TimeSlices[i+1])||((Time > TimeSlices[i])&&(Time <= TimeSlices[i+1])))
            return TimeSlices[i];
    }
}

G4double GateClock::GetCurrentTimeSliceEnd()
{
    for (G4int i = 0; i < TimeSlices.size(); i++)
    {
        if (TimeSlices[i+1])
            if ((Time > TimeSlices[i])&&(Time <= TimeSlices[i+1]))
                return TimeSlices[i+1];
            else
                return TimeEnd;
    }
}

void GateClock::SetTimeSlices(std::vector<G4double> timeSlices)
{
    TimeSlices = timeSlices;
}

G4int GateClock::GetCurrentActivitySlice()
{
    for (G4int i = 0; i < TimeSlices.size(); i++)
    {
        if ((!TimeSlices[i+1])||((Time > TimeSlices[i])&&(Time <= TimeSlices[i+1])))
            return ActivitySlices[i];
    }
}

void GateClock::SetActivitySlices(std::vector<G4int> activitySlices)
{
    ActivitySlices = activitySlices;
}

bool GateClock::NextSlice()
{
    for (G4int i = 0; i < TimeSlices.size(); i++)
    {
        if (!TimeSlices[i+1])
            return 0;
        else if ((Time > TimeSlices[i])&&(Time <= TimeSlices[i+1]))
        {
            Time = TimeSlices[i+1];
            return 1;
        }
    }
}



