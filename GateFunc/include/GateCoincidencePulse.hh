#ifndef GATECOINCIDENCEPULSE_HH
#define GATECOINCIDENCEPULSE_HH

#include "GatePulse.hh"

#include <vector>

class GateCoincidencePulse : public std::vector<GatePulse*>
{
public:
    inline GateCoincidencePulse(GatePulse *firstPulse, G4double coincidenceWindow)
    {
        push_back(firstPulse);
        StartTime = firstPulse->GetTime();
        EndTime = StartTime + coincidenceWindow;
    }

    virtual ~GateCoincidencePulse(){}

    inline G4double GetStartTime() const
    {
        return StartTime;
    }

    inline G4double GetEndTime() const
    {
        return EndTime;
    }

    virtual inline G4bool IsInCoincidence(GatePulse* newPulse) const
    {
        return  ((newPulse->GetTime() >= StartTime) && (newPulse->GetTime() < EndTime));
    }

    virtual inline G4bool IsAfterWindow(GatePulse* newPulse) const
    {
        return (newPulse->GetTime() >= EndTime);
    }

private:
    G4double StartTime;
    G4double EndTime;
};

#endif // GATECOINCIDENCEPULSE_HH
