#ifndef GATECLOCK_HH
#define GATECLOCK_HH

#include "globals.hh"
#include "G4ios.hh"

class GateClock
{

public:
    static GateClock* GetInstance()
    {
        if (Instance == 0)
            Instance = new GateClock();
        return Instance;
    }

    ~GateClock();

    G4double GetStartTime() { return TimeStart; }
    void SetStartTime( G4double time ) { TimeStart = time; }

    G4double GetEndTime() { return TimeEnd; }
    void SetEndTime( G4double time ) { TimeEnd = time; }

    G4double GetCurrentTime() { return Time; }
    void SetCurrentTime( G4double time ) { Time = time; }

    void SetFrameVector(std::vector<G4double> frameVector) { FrameVector = frameVector; }
    std::vector<G4double> GetFrameVector() { return FrameVector; }

    G4double GetCurrentTimeSliceStart();
    G4double GetCurrentTimeSliceEnd();

    bool NextSlice();

private:
    GateClock();

    static GateClock* Instance;
    std::vector<G4double> FrameVector;
    std::vector<G4int> ActivitySlices;

    G4double Time;
    //thread_local G4double TimeLocal;

    G4double TimeStart;
    G4double TimeEnd;
};

#endif
