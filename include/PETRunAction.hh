#ifndef PETRUNACTION_HH
#define PETRUNACTION_HH

#include "GateCoincidencePulse.hh"
#include "GatePulseCollection.hh"

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>
#include <deque>

class PETRunAction : public G4UserRunAction
{
public:

    PETRunAction();
    virtual ~PETRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    void FindCoincidences(std::vector<GatePulseCollection*>* collections);

    std::deque<GateCoincidencePulse*> CoincidencePulses;
    G4double CoincidenceWindow;
};

#endif // PETRUNACTION_HH
