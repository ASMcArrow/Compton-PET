#ifndef PETSTEPPINGACTION_H
#define PETSTEPPINGACTION_H

#include "G4UserSteppingAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class PrimaryGeneratorAction;

class PETSteppingAction : public G4UserSteppingAction {

public:
    PETSteppingAction()
    {}

    ~PETSteppingAction()
    {}

    void UserSteppingAction(const G4Step* aStep);
};

#endif
