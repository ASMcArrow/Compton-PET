#ifndef PETPHYSICSLIST_H
#define PETPHYSICSLIST_H

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PETPhysicsList: public G4VModularPhysicsList
{
public:

    PETPhysicsList();
    virtual ~PETPhysicsList();

    void SetCuts();
    void AddParallelScoring();
    void ConstructProcess();

private:
    G4double cutForGamma;
    G4double cutForElectron;
    G4double cutForPositron;
};

#endif
