#ifndef PETDETECTORSD_HH
#define PETDETECTORSD_HH

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

class PETRunAction : public G4UserRunAction
{
public:

    PETRunAction();
    virtual ~PETRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:

};

#endif // PETDETECTORSD_HH
